#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file service.py
## @brief Interactive wrapper for access to Instrument Services via gRPC
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install folder
from .base import Base
from picarro.io.protobuf import ProtoBuf

### Third-party modules
import grpc

### Standard Python modules
from typing import Union
import importlib
import logging

class Service (Base):

    """Base for gRPC service request handlers.  It automates lookup of service
    address (interface adress and port number) from the settings file based on
    service name.

    To facilitate service name lookup, subclasses should also derive from a
    `Servicer` class, generated by the gRPC compiler from the relevant `service`
    block within a `.proto` file.  For instance, let's say say you have a
    `example_service.proto` file containing:

    ```
    syntax = "proto3";
    import "google/protobuf/wrappers.proto";
    service Example {
       rpc echo (google.protobuf.StringValue)
           returns (google.protobuf.StringValue);
    }
    ```

    Then, your service handler might look something like this:

    ```
    from picarro.messaging.grpc.service import Service
    from example_service_pb2_grpc import ExampleServicer
    from google.protobuf.wrappers_pb2 import StringValue
    from grpc import ServicerContext

    class ExampleService (Service, ExampleServicer):

        def echo(self,
                 request : StringValue,
                 context : ServicerContext) -> StringValue:
           '''Handle and respond to gRPC `echo()` invocations'''

           return StringValue(
               value = f"I received from you: {request.value}")
    ```

    """

    def __init__ (self, bind_address=""):
        Base.__init__ (self,
                       service_name = self.service_name or self._service_name())

        self.bind_address = self.realaddress(bind_address, "interface", "port", "[::]", 8080)

    def add_to_server(self,
                      server       : Union[grpc.Server, grpc.aio.Server],
                      add_listener : bool = True):

        '''Add this service handler to a gRPC server.

        @param[in] server
            gRPC server instance

        @param[in] add_listener
            Whether to also add the a listener port that was passed to
            __init__() and/or the configured settings for this service
            (see `grpc-services-common.json` for details).
        '''

        servicer_name, servicer_base = self._servicer_name_and_base()
        servicer_module = importlib.import_module(servicer_base.__module__)
        add_method = getattr(servicer_module, 'add_%s_to_server'%(servicer_name,))
        add_method(self, server)
        if add_listener:
            logging.info('Adding service %r listener: %s'%(
                self.service_name,
                self.bind_address))
            server.add_insecure_port(self.bind_address)

    def _wrap (self, method, *args, **kwargs):
        if response := method(*args, **kwargs):
            return response
        else:
            return ProtoBuf.Empty()


    SERVICER_SUFFIX = 'Servicer'

    @classmethod
    def _servicer_name_and_base(cls):
        for candidate in cls.__mro__:
            if candidate.__name__.endswith(cls.SERVICER_SUFFIX):
                return candidate.__name__, candidate
        else:
            raise TypeError(
                'gRPC service class %r must derive from a generated Servicer base'%
                (cls.__name__,))

    @classmethod
    def _service_name(cls):
        servicer_name, _ = cls._servicer_name_and_base()
        service_name, _ = servicer_name.rsplit(cls.SERVICER_SUFFIX)
        return service_name
