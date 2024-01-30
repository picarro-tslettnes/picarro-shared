#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file server.py
## @brief ZeroMQ publisher - ProtoBuf flavor
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

from .requesthandler    import RequestHandler
from ..basic.responder  import Responder
from ...google.protobuf import Picarro, ProtoBuf

import logging

class Server (Responder):
    '''ZMQ RPC server using ProtoBuf messages'''

    def __init__(self,
                 bind_address : str,
                 channel_name : str):

        Responder.__init__(self, bind_address, channel_name)
        self.request_handlers = {}

    def add_request_handler(self,
                            interface_name: str,
                            handler: RequestHandler):

        self.request_handlers[interface_name] = handler

    def process_request(self, binary_request: bytes):
        reply = Picarro.RR.Reply()

        try:
            request = Picarro.RR.Request.FromString(binary_request)
        except ProtoBuf.DecodeError as e:
            logging.warning('ZMQ RPC server failed to decode ProtoBuf request: %s'%
                            (binary_request,))
            RequestHandler.insert_error(
                reply,
                Picarro.RR.STATUS_INVALID,
                str(e),
                flow = Picarro.Status.FLOW_CANCELLED,
                symbol = type(e).__name__,
                attributes = dict(
                    data = binary_request
                )
            )
        else:
            logging.debug('ZMQ RPC server handling request: %s'%(
                ProtoBuf.MessageToString(request, as_one_line=True),))
            self.process_protobuf_request(request, reply)

        logging.debug('ZMQ RPC server sending reply: %s'%(
            ProtoBuf.MessageToString(reply, as_one_line=True),))

        return reply.SerializeToString()


    def process_protobuf_request(self,
                                 request : Picarro.RR.Request,
                                 reply   : Picarro.RR.Reply):

        reply.client_id = request.client_id
        reply.request_id = request.request_id

        try:
            handler = self.request_handlers[request.interface_name]
        except KeyError:
            RequestHandler.insert_error(
                reply,
                Picarro.RR.STATUS_INVALID,
                "No such RPC interface",
                flow = Picarro.Status.FLOW_CANCELLED,
                symbol = 'KeyError',
                attributes = dict(
                    interface_name = request.interface_name
                )
            )
        else:
            handler.process_method_request(request, reply)
