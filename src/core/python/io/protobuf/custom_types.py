#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file protobuf_custom_types.py
## @brief Convience wrappers for Picarro shared types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

from .standard_types import ProtoBuf
from typing          import Tuple

import picarro.core.paths
import sys

## Python code generated by the ProtoBuf compiler goes into the `generated`
## subfolder. However, that code is itself unaware of this fact, so we need
## to append that folder to Python's module search path.
_pythonRoot, _generatedRoot = picarro.core.paths.locateDominatingPath('generated')
sys.path.append(_generatedRoot)

## In lieu of proper package-based code generation, we create a `Picarro` container
## class to hold generated data types within the ProtoBuf `Picarro` namespace.
## Within here we import generated modules using names that reflect the
## second component on their ProtoBuf namespace (e.g. `Picarro.Variant`).
##
## You can add to this class by importing it under a different name, then create
## an `Picarro` subclass; e.g.:
##
##   ```
##   from core.io.protobuf import Picarro as Picarro_Core
##
##   class Picarro (Picarro_Core):
##       import generated.my_module_pb2 as MyModule
##   ```
##
##  Now you have a `Picarro` "namespace" that includes these basic types as
##  well as your own.
##
##  For an example of this, see [demo/core/types.py](../../../../mantle/apps/demo/python/demo/core/types.py).

class Picarro (object):
    import generated.event_types_pb2 as Status
    import generated.signal_types_pb2 as Signal
    import generated.variant_types_pb2 as Variant
    import generated.request_reply_pb2 as RR

    @classmethod
    def encodeValue(cls, value : object):
        if isinstance(value, tuple) and len(value) == 2 and isinstance(value[0], str):
            return cls.encodeTaggedValue(value)
        else:
            return cls.encodeTaggedValue((None, value))

    @classmethod
    def encodeTaggedValue(cls, pair : Tuple[str, object]):
        tag, value = pair

        tv = Picarro.Variant.Value(tag=tag)

        if isinstance(value, bool):
            tv.value_bool = value

        elif isinstance(value, int) and (value >= 0):
            tv.value_uint = value

        elif isinstance(value, int):
            tv.value_sint = value

        elif isinstance(value, float):
            tv.value_real = value

        elif isinstance(value, str):
            tv.value_string = value

        elif isinstance(value, bytes):
            tv.value_bytes = value

        elif isinstance(value, ProtoBuf.Timestamp):
            tv.value_timestamp.CopyFrom(value)

        elif isinstance(value, ProtoBuf.Duration):
            tv.value_duration.CopyFrom(value)

        elif isinstance(value, (list, tuple)):
            tv.value_list.items.extend([
                cls.encodeValue(item) for item in value])

        elif isinstance(value, dict):
            tv.value_list.items.extend([
                cls.encodeTaggedValue(item) for item in value.items()])
            tv.value_list.mappable = True

        elif value is not None:
            raise TypeError("Cannot convert type %s to protobuf value: %s"%
                            (type(value), value))
        return tv


    @classmethod
    def decodeValue(cls, v, autotype=True):
        fieldname = v.WhichOneof('value')

        if (fieldname == 'value_timestamp'):
            value = cls.decodeTimestamp(v.value_timestamp)
        elif (fieldname == 'value_duration'):
            value = cls.decodeDuration(v.value_duration)
        elif (fieldname == 'value_list'):
            if autotype and v.value_list.untagged:
                value = [ cls.decodeValue(tv, autotype)
                          for tv in v.value_list.items ]
            else:
                value = [ cls.decodeTaggedValue(tv, autotype)
                          for tv in v.value_list.items ]
                if autotype and v.value_list.mappable:
                    value = dict(value)
        elif fieldname:
            value = getattr(v, fieldname)
        else:
            value = None
        return value


    @classmethod
    def decodeTaggedValue(cls, tv, autotype=True):
        tag = None
        if tv and tv.tag:
            tag = tv.tag
            value = cls.decodeValue(tv, autotype)
        return (tag, value)


    @classmethod
    def encodeValueList(cls, value):
        if value is None:
            return Picarro.Variant.ValueList()

        elif isinstance(value, dict):
            return Picarro.Variant.ValueList(
                items = [cls.encodeTaggedValue(tv) for tv in value.items()],
                mappable = True)

        elif isinstance(value, list):
            return Picarro.Variant.ValueList(
                items = [cls.encodeValue(v) for v in value])

        elif isinstance(value, Picarro.Variant.ValueList):
            return value

        else:
            raise ValueError("encodeToValueList() expects a dictionary or list")


    @classmethod
    def decodeTaggedValueList(cls, valuelist, autotype=True):
        if isinstance(valuelist, Picarro.Variant.ValueList):
            return [cls.decodeTaggedValue(tv, autotype) for tv in valuelist.items]
        else:
            raise ValueError("Argument must be a Picarro.Variant.ValueList() instance")

    @classmethod
    def decodeValueList(cls, valuelist, autotype=True):
        return [v for (t,v) in self.decodeTaggedValueList(valuelist, autotype)]

    @classmethod
    def decodeValueMap(cls, valuelist, autotype=True):
        return dict(cls.decodeTaggedValueList(valuelist, autotype))

    @classmethod
    def valueList(cls, **kwargs):
        return cls.encodeValueList(kwargs)