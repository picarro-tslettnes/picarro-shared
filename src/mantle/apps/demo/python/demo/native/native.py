#!/bin/echo Do not invoke directly.
#===============================================================================
## @file demo.py
## @brief Demo - native Python implementation
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from ..core          import API, Picarro, ProtoBuf, demo_signals
from picarro.core.scheduler  import scheduler, ALIGN_UTC
from picarro.core.invocation import safe_invoke

### Standard Python modules
from typing import Callable
import time, sys, os.path


#===============================================================================
# Native Demo implementation

class NativeDemo (API):
    '''Demo API'''

    def __init__(self):
        API.__init__(self, 'Python Native')
        self.timer_task_handle = "Demo.ticker"

    def say_hello(self, greeting: Picarro.Demo.Greeting):
        print("Emitting greeting: say_hello(%s)"%(
            ProtoBuf.MessageToString(greeting, as_one_line=True),))
        demo_signals.emit_mapping('greeting', None, greeting.identity, greeting)


    def get_current_time(self) -> Picarro.Demo.TimeData:
        '''
        Get current time data.
        @return
            Current time data provided by the specific implementation.
        '''
        t = time.time()
        return Picarro.Demo.TimeData(
            timestamp = ProtoBuf.encodeTimestamp(t),
            local_time = Picarro.encodeTimeStruct(time.localtime(t)),
            utc_time = Picarro.encodeTimeStruct(time.gmtime(t)),
        )


    def start_ticking(self) -> None:
        '''
        Tell the server to start issuing periodic time updates
        '''
        scheduler.schedule(self.timer_task_handle, # handle
                           1.0,                    # interval
                           self._emit_time,        # method
                           align = ALIGN_UTC)          # time alignment


    def stop_ticking(self) -> None:
        '''
        Tell the server to stop issuing periodic time updates
        '''
        scheduler.unschedule(self.timer_task_handle)

    def _emit_time(self):
        t = time.time()
        demo_signals.emit_event(
            'time',
            Picarro.Demo.TimeData(
                timestamp = ProtoBuf.encodeTimestamp(t),
                local_time = Picarro.encodeTimeStruct(time.localtime(t)),
                utc_time = Picarro.encodeTimeStruct(time.gmtime(t)),
            ))
