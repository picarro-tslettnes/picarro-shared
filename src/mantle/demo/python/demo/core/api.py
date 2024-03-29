#!/bin/echo Do not invoke directly.
#===============================================================================
## @file demo.py
## @brief Demo - native Python implementation
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from .types   import Picarro, ProtoBuf
from .signals import demo_signals

### Standard Python modules
from typing import Callable
import sys, os.path, time

SignalSlot = Callable[[Picarro.Demo.Signal], None]

#===============================================================================
# Native Demo implementation

class API (ProtoBuf):
    '''Demo API'''

    def __init__(self,
                 implementation : str,
                 identity       : str = None):

        self.implementation = implementation or str(self)
        self.birth          = time.time()
        self.identity       = identity or os.path.basename(sys.argv[0])

    def hello(self,
              text: str,
              **kwargs):
        '''Say hello to anyone who might be listening.

        @param[in] text
            What we're telling our listeners
        @param[in] kwargs
            Arbitrary attributes included in greeting
        @note
            This is a convencience wrapper to build a `Picarro.Demo.Greeting` object
            and pass it to `say_hello()`.
        '''

        greeting = Picarro.Demo.Greeting(text=text,
                                    identity=self.identity,
                                    implementation=self.implementation,
                                    birth=ProtoBuf.encodeTimestamp(self.birth),
                                    data=Picarro.encodeValueList(kwargs))

        return self.say_hello(greeting)


    def say_hello(self, greeting: Picarro.Demo.Greeting):
        '''Issue a greeting to anyone who may be listening.
        For interactive use, the `hello()` wrapper method may be more convenient.

        @param[in] greeting
            A greeting for our listeners.
        '''

        raise NotImplementedError("Method not implemented by %s"%(self,))


    def get_current_time(self) -> Picarro.Demo.TimeData:
        '''Get current time data.

        @return
            Current time data provided by the specific implementation.
        '''

        raise NotImplementedError("Method not implemented by %s"%(self,))


    def start_ticking(self) -> None:
        '''
        Tell the server to start issuing periodic time updates
        '''
        raise NotImplementedError("Method not implemented by %s"%(self,))


    def stop_ticking(self) -> None:
        '''
        Tell the server to stop issuing periodic time updates
        '''
        raise NotImplementedError("Method not implemented by %s"%(self,))


    def start_notify_greetings(self, callback: SignalSlot):
        '''Register a callback to be invoked whenever a greeting is received

        @param[in] callback
            Callback method, which will receive the Picarro.Demo.Signal() message
            containing the greeting as argument.
        '''
        demo_signals.connect_signal('greeting', callback)


    def stop_notify_greetings(self):
        '''
        Unregister any existing greeting callback
        '''
        demo_signals.disconnect_signal('greeting')


    def start_notify_time(self, callback: SignalSlot):
        '''
        @brief Register a callback to be invoked whenver the time updated (1x/second)

        @param[in] callback
            Callback method, which will receive the time data as argument.
        '''
        demo_signals.connect_signal_data('time', callback)


    def stop_notify_time (self):
        '''
        @brief Unregister any existing time callbacks
        '''

        demo_signals.disconnect_signal('time')
