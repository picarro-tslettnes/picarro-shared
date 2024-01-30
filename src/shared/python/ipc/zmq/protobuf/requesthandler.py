#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file requesthandler.py
## @brief ZeroMQ RPC request handler using ProtoBuf payloads
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

from ...google.protobuf import Picarro, ProtoBuf

from typing  import Callable
from inspect import getfullargspec

class RequestHandler (object):
    '''Handle RPC requests received as ProtoBuf `Picarro.RR.Request` messages.

    The `Request` message is processed as follows:

    * The `interface_name` corresponds to this handler instance.

    * The `method_name` is used to look up a handler method within this class.
      This handler method should take a single ProtoBuf message as input,
      and return a single ProtoBuf message.

    * The `param` field is deserialized as a ProtoBuf message based on the
      annotated signature of the handler method.

    * The handler method is invoked with the deserialized input argument.

    * The return value from the handler method is serialized and incorportaed
      into the `param` field of the `Reply` message which will be sent back to
      the caller.

    * If the handler method raises an exception, the exception data is
      captured into the `status` field of the `Reply` message.

    * The resulting `Reply` message is sent back to the client.

    `Request` messages and generate corresponding `Reply`


    Subclasses should define handler methods with the following criteria:

    * The method name must start with "`handle_`"; the remainder of its name
      maps directly to the expected `method_name` field of the `Request`.

    * It should take one single ProtoBuf message as input argument, and
      include a Python annotation to indicate the specific message type.
      This message type is used to deserialize the input.

    * It should return a single ProtoBuf message, which is then serialized
      and sent back in the `Reply` message to the client.

    ### Example:

    ```
    class MyRequstHandler (ipc.zmq.protobuf.requesthandler.RequestHandler):

        interface_name = 'My RPC Service'

        def handle_my_request(self, arg: MyProtoBufRequestType) -> MyProtoBufReplyType:
            # Do something here
            return MyProtoBufReplyType(myfield='my value', ...)
    ```

    '''

    def __init__ (self, interface_name : str):
        self.interface_name = interface_name

    def process_method_request(self,
                               request : Picarro.RR.Request,
                               reply   : Picarro.RR.Reply):

        try:
            handler = getattr(self, 'handle_' + request.method_name)
        except AttributeError:
            self.insert_error(
                reply,
                Picarro.RR.STATUS_INVALID,
                'Requested method not found',
                symbol = 'NotFound',
                flow = Picarro.Status.FLOW_CANCELLED,
                attributes = dict(
                    interface_name = request.interface_name,
                    method_name = request.method_name
                )
            )
        else:
            self._process_handler_invocation(handler, request, reply)

        return reply

    def _process_handler_invocation(self,
                        handler: Callable[[ProtoBuf.Message], ProtoBuf.Message],
                        request: Picarro.RR.Request,
                        reply  : Picarro.RR.Reply):

        argspec = getfullargspec(handler)
        try:
            argname = argspec.args[1] # Bypass the 1st argument (self)
            annotated_type = argspec.annotations[argname]
            arg = annotated_type.FromString(request.param.serialized_proto)

        except (KeyError, IndexError, AttributeError):
            self.insert_error(
                reply,
                Picarro.RR.STATUS_FAILED,
                "Handler method does not have an input argument "
                "with a ProtoBuf message annottation",
                symbol = 'InvalidHandlerMethod',
                flow = Picarro.Status.FLOW_CANCELLED,
                attributes = dict(
                    interface_name = self.interface_name,
                    method_name = handler.__name__
                )
            )

        else:
            self._invoke_handler(handler, arg, reply)



    def _invoke_handler(self,
                        handler: Callable[[ProtoBuf.Message], ProtoBuf.Message],
                        arg    : ProtoBuf.Message,
                        reply  : Picarro.RR.Reply):

        try:
            result = handler(arg)
        except Exception as e:
            self.insert_error(
                reply,
                Picarro.RR.STATUS_FAILED,
                str(e),
                symbol = type(e).__name__,
                flow = Picarro.Status.FLOW_ABORTED,
                attributes = dict(
                    exception_args = e.args
                )
            )
        else:
            reply.serialized_proto = result.SerializeToString()


    @classmethod
    def insert_error(self,
                     reply      : Picarro.RR.Reply,
                     code       : Picarro.RR.StatusCode,
                     text       : str,
                     symbol     : str = '',
                     flow       : Picarro.Status.Flow = Picarro.Status.FLOW_NONE,
                     attributes : dict = {}):

        reply.status.code = code
        reply.status.details.text = text
        reply.status.details.domain = Picarro.Status.DOMAIN_APPLICATION
        reply.status.details.symbol = symbol
        reply.status.details.level = Picarro.Status.LEVEL_FAILED
        reply.status.details.flow = flow
        Picarro.encodeToValueList(attributes, reply.status.details.attributes)
