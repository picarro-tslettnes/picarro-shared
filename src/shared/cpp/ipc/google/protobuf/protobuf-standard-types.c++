/// -*- c++ -*-
//==============================================================================
/// @file protobuf-standard-types.c++
/// @brief Encode/decode routines for ProtoBuf types provided by Google
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "protobuf-standard-types.h++"
#include "protobuf-inline.h++"

#include <utility>

namespace picarro::protobuf
{
    void encode(const std::string &s,
                google::protobuf::StringValue *msg) noexcept
    {
        msg->set_value(s);
    }

    void decode(const google::protobuf::StringValue &msg,
                std::string *s) noexcept
    {
        *s = msg.value();
    }

    void encode(double r,
                google::protobuf::DoubleValue *msg) noexcept
    {
        msg->set_value(r);
    }

    void decode(const google::protobuf::DoubleValue &msg,
                double *r) noexcept
    {
        *r = msg.value();
    }

    void encode(float r,
                google::protobuf::FloatValue *msg) noexcept
    {
        msg->set_value(r);
    }

    void decode(const google::protobuf::FloatValue &msg,
                float *r) noexcept
    {
        *r = msg.value();
    }

    void encode(std::uint64_t n,
                google::protobuf::UInt64Value *msg) noexcept
    {
        msg->set_value(n);
    }

    void decode(const google::protobuf::UInt64Value &msg,
                std::uint64_t *n) noexcept
    {
        *n = msg.value();
    }

    void encode(std::int64_t n,
                google::protobuf::Int64Value *msg) noexcept
    {
        msg->set_value(n);
    }

    void decode(const google::protobuf::Int64Value &msg,
                std::int64_t *n) noexcept
    {
        *n = msg.value();
    }

    void encode(std::uint32_t n,
                google::protobuf::UInt32Value *msg) noexcept
    {
        msg->set_value(n);
    }

    void decode(const google::protobuf::UInt32Value &msg,
                std::uint32_t *n) noexcept
    {
        *n = msg.value();
    }

    void encode(std::int32_t n,
                google::protobuf::Int32Value *msg) noexcept
    {
        msg->set_value(n);
    }

    void decode(const google::protobuf::Int32Value &msg,
                std::int32_t *n) noexcept
    {
        *n = msg.value();
    }

    void encode(bool b,
                google::protobuf::BoolValue *msg) noexcept
    {
        msg->set_value(b);
    }

    void decode(const google::protobuf::BoolValue &msg,
                bool *b) noexcept
    {
        *b = msg.value();
    }

    void encode(const picarro::types::Bytes &b,
                google::protobuf::BytesValue *msg) noexcept
    {
        msg->set_value(b.data(), b.size());
    }

    void decode(const google::protobuf::BytesValue &msg,
                picarro::types::Bytes *b) noexcept
    {
        b->assign(msg.value().begin(), msg.value().end());
    }

    void encode(const picarro::dt::TimePoint &tp,
                google::protobuf::Timestamp *ts) noexcept
    {
        timespec tspec = picarro::dt::to_timespec(tp);
        ts->set_seconds(tspec.tv_sec);
        ts->set_nanos((int)tspec.tv_nsec);
    }

    void decode(const google::protobuf::Timestamp &ts,
                picarro::dt::TimePoint *tp) noexcept
    {
        *tp = picarro::dt::to_timepoint(ts.seconds(), ts.nanos());
    }

    void encode(const picarro::dt::Duration &duration,
                google::protobuf::Duration *msg) noexcept
    {
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(duration);
        if (secs > duration)
            secs -= std::chrono::seconds(1);
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(duration - secs);
        msg->set_seconds(secs.count());
        msg->set_nanos(nanos.count());
    }

    void decode(const google::protobuf::Duration &msg,
                picarro::dt::Duration *duration) noexcept
    {
        *duration = (std::chrono::seconds(msg.seconds()) +
                     std::chrono::nanoseconds(msg.nanos()));
    }

    void encode(const picarro::types::Value &value,
                google::protobuf::Value *msg) noexcept
    {
        switch (value.type())
        {
        case picarro::types::ValueType::NONE:
            msg->set_null_value({});
            break;

        case picarro::types::ValueType::BOOL:
            msg->set_bool_value(value.as_bool());
            break;

        case picarro::types::ValueType::UINT:
        case picarro::types::ValueType::SINT:
        case picarro::types::ValueType::REAL:
        case picarro::types::ValueType::TIMEPOINT:
        case picarro::types::ValueType::DURATION:
        case picarro::types::ValueType::COMPLEX:
            msg->set_number_value(value.as_real());
            break;

        case picarro::types::ValueType::CHAR:
        case picarro::types::ValueType::STRING:
            msg->set_string_value(value.as_string());
            break;

        case picarro::types::ValueType::BYTEVECTOR:
            msg->set_string_value(value.as_bytevector().to_string());
            break;

        case picarro::types::ValueType::VALUELIST:
            encode(*value.get_valuelist(), msg->mutable_list_value());
            break;

        case picarro::types::ValueType::KVMAP:
            encode(*value.get_kvmap(), msg->mutable_struct_value());
            break;

        case picarro::types::ValueType::TVLIST:
            encode(*value.get_tvlist(), msg->mutable_struct_value());
            break;

        default:
            break;
        }
    }

    void decode(const google::protobuf::Value &msg,
                picarro::types::Value *value) noexcept
    {
        switch (msg.kind_case())
        {
        case google::protobuf::Value::kNullValue:
            *value = {};
            break;

        case google::protobuf::Value::kNumberValue:
            *value = msg.number_value();
            break;

        case google::protobuf::Value::kStringValue:
            *value = msg.string_value();
            break;

        case google::protobuf::Value::kBoolValue:
            *value = msg.bool_value();
            break;

        case google::protobuf::Value::kStructValue:
            *value = protobuf::decoded<types::KeyValueMap>(msg.struct_value());
            break;

        case google::protobuf::Value::kListValue:
            *value = protobuf::decoded<types::ValueList>(msg.list_value());
            break;

        default:
            break;
        }
    }

    void encode(const picarro::types::KeyValueMap &kvmap,
                google::protobuf::Struct *msg) noexcept
    {
        auto fields = msg->mutable_fields();
        for (const auto &[key, value] : kvmap)
        {
            encode(value, &(*fields)[key]);
        }
    }

    void decode(const google::protobuf::Struct &msg,
                picarro::types::KeyValueMap *kvmap) noexcept
    {
        for (const auto &[key, value] : msg.fields())
        {
            decode(value, &(*kvmap)[key]);
        }
    }

    void encode(const picarro::types::TaggedValueList &tvlist,
                google::protobuf::Struct *msg) noexcept
    {
        auto fields = msg->mutable_fields();
        for (const auto &[key, value] : tvlist)
        {
            if (key)
            {
                encode(value, &(*fields)[*key]);
            }
        }
    }

    void decode(const google::protobuf::Struct &msg,
                picarro::types::TaggedValueList *tvlist) noexcept
    {
        const auto &fields = msg.fields();
        tvlist->reserve(fields.size());
        for (const auto &[key, value] : fields)
        {
            picarro::types::TaggedValue tv = {key, {}};
            decode(value, &tv.second);
            tvlist->push_back(std::move(tv));
        }
    }

    void encode(const picarro::types::ValueList &list,
                google::protobuf::ListValue *msg) noexcept
    {
        for (const picarro::types::Value &value : list)
        {
            encode(value, msg->add_values());
        }
    }

    void decode(const google::protobuf::ListValue &msg,
                picarro::types::ValueList *list) noexcept
    {
        list->reserve(msg.values_size());
        for (const google::protobuf::Value &value : msg.values())
        {
            decode(value, &list->emplace_back());
        }
    }
}  // namespace picarro::protobuf
