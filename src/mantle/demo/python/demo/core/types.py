#!/bin/echo Do not invoke directly.
#===============================================================================
## @file demo_types.py
## @brief Common types and definitions for Python 'Demo' service
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules relative to install dir
from picarro.io.protobuf import Picarro as Picarro_Base, ProtoBuf
from picarro.core.scalar_types import enums

### Standard Python modules
import time

class Picarro (Picarro_Base):
    import generated.demo_pb2 as Demo

    @classmethod
    def encodeTimeStruct(cls, ts):
        return Picarro.Demo.TimeStruct(
            year = ts.tm_year,
            month = ts.tm_mon,
            day = ts.tm_mday,
            hour = ts.tm_hour,
            minute = ts.tm_min,
            second = ts.tm_sec,
            weekday = (ts.tm_wday+1)%7,
            year_day = ts.tm_yday,
            is_dst = ts.tm_isdst)

    @classmethod
    def decodeTimeStruct (cls, ts):
        return time.time_struct((ts.year, ts.month, ts.day,
                                 ts.hour, ts.minute, ts.second,
                                 (ts.weekday-1)%7, ts.year_day, ts.is_dst))


Weekdays = enums(Picarro.Demo.Weekday, globals())
