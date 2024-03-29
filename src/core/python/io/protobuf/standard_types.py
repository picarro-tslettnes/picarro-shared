#!/usr/bin/echo Do not invoke directly.
#===============================================================================
## @file protobuf_standard_types.py
## @brief Convience wrappers for Google ProtoBuf types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

class ProtoBuf (object):
    import google.protobuf.text_format as text_format
    import google.protobuf.json_format as json_format

    from google.protobuf.text_format import MessageToString
    from google.protobuf.json_format import MessageToDict
    from google.protobuf.json_format import ParseDict

    from google.protobuf.pyext.cpp_message import \
        GeneratedProtocolMessageType as MessageType
    from google.protobuf.message import Message, Error, EncodeError, DecodeError
    from google.protobuf.empty_pb2 import Empty
    from google.protobuf.duration_pb2 import Duration
    from google.protobuf.timestamp_pb2 import Timestamp
    from google.protobuf.wrappers_pb2 import \
        BoolValue, StringValue, DoubleValue, FloatValue, \
        Int64Value, UInt64Value, Int32Value, UInt32Value, \
        BytesValue
    from google.protobuf.struct_pb2 import Value, ListValue, Struct


    @classmethod
    def decodeTimestamp(cls, prototime):
        return prototime.seconds + prototime.nanos*1e-9

    @classmethod
    def encodeTimestamp(cls, timestamp):
        from datetime import datetime
        from time import struct_time, mktime

        ts = ProtoBuf.Timestamp()

        if isinstance(timestamp, ProtoBuf.Timestamp):
            ts.CopyFrom(timestamp)

        elif isinstance(timestamp, int):
            ts.seconds = timestamp

        elif isinstance(timestamp, float):
            ts.seconds = int(timestamp)
            ts.nanos = int((timestamp-int(timestamp))*1e9)

        elif isinstance(timestamp, str):
            ts.FromJsonString(timestamp)

        elif isinstance(timestamp, struct_time):
            ts.seconds = int(mktime(timestamp))

        elif isinstance(timestamp, datetime):
            ts.FromDatetime(timestamp)

        elif timestamp is not None:
            raise TypeError("Cannot encode ProtoBuf timestamp from %s"%(type(timestamp).__name__,))

        return ts


    @classmethod
    def decodeDuration(cls, duration):
        return duration.seconds + duration.nanos*1e-9


    @classmethod
    def encodeDuration(cls, duration):
        if duration:
            return cls.Duration(seconds=int(duration),
                               nanos=int((duration-int(duration))*1e9))

    @classmethod
    def encodeValue (cls, value) -> Value:
        if value is None:
            return Value(null_value=protobuf.NullValue())

        elif isinstance(value, bool):
            return Value(bool_value=value)

        elif isinstance(value, (int, float)):
            return Value(number_value=value)

        elif isinstance(value, str):
            return Value(string_value=value)

        elif isinstance(value, dict):
            return Value(struct_value=cls.encodeProtoStruct(value))

        elif isinstance(value, list):
            return Value(list_value=cls.encodeProtoList(value))

        else:
            raise ValueError("Unable to encode value type %r as protobuf.Value"%
                             (type(value).__name__))


    @classmethod
    def encodeStruct (cls, dictionary: dict) -> Struct:
        items = [ (key, cls.encodeProtoValue(value))
                  for (key, value) in dictionary.items() ]
        return ProtoBuf.Struct(fields=dict(items))

    @classmethod
    def encodeListValue (cls, listvalue: list) -> ListValue:
        elist = [ cls.encodeProtoValue(value)
                  for value in listvalue ]
        return ProtoBuf.ListValue(values=elist)


    @classmethod
    def decodeValue (cls, value: Value) -> object:
        kind = v.WhichOneof('kind')
        if kind == 'null_value':
            return None
        elif kind == 'bool_value':
            return value.bool_value
        elif kind == 'number_value':
            if value.number_value.is_integer():
                return int(value.number_value)
            else:
                return value.number_value
        elif kind == 'string_value':
            return value.string_value
        elif kind == 'struct_value':
            return cls.decodeStruct(value.struct_value)
        elif kind == 'list_value':
            return cls.decodeListValue(value.list_value)
        else:
            return None

    @classmethod
    def decodeStruct(cls, structvalue: Struct) -> dict:
        return dict([(key, cls.decodeValue(value))
                     for (key, value) in structvalue.fields.items()])

    @classmethod
    def decodeListValue(cls, listvalue: ListValue) -> list:
        return [ cls.decodeValue(value)
                 for value in listvalue.values ]


    @classmethod
    def decodeToDict(cls,
                     message : Message,
                     use_integers_for_enums : bool = True,
                     including_default_value_fields : bool = False):

        return cls.json_format.MessageToDict(
            message,
            including_default_value_fields=including_default_value_fields,
            use_integers_for_enums=use_integers_for_enums,
            preserving_proto_field_name=True)


    @classmethod
    def encodeFromDict(cls,
                       value     : dict,
                       prototype : MessageType,
                       ignore_unknown_fields : bool = False):

        msg = prototype()
        cls.json_format.ParseDict(
            value,
            msg,
            ignore_unknown_fields = ignore_unknown_fields)
        return msg

    @classmethod
    def check_type(cls,
                   value : Message,
                   expected: MessageType = Message):

        assert isinstance(expected, ProtoBuf.MessageType)

        if not isinstance(value, expected):
            raise TypeError('Expected %s, not %s'%
                            (expected.DESCRIPTOR.full_name, type(value).__name__)) from None

    @classmethod
    def print(cls, message: Message, as_one_line=True):
        print(cls.MessageToString(message, as_one_line=as_one_line))

    @classmethod
    def print_dict(cls, message: Message):
        print(cls.MessageToDict(message))
