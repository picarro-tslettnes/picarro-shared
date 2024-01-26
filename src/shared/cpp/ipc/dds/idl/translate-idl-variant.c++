/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-variant.c++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-variant.h++"
#include "translate-idl-inline.h++"

namespace picarro::idl
{
    //==========================================================================
    // Encode/decode Value

    void encode(const picarro::types::Value &value,
                Picarro::Variant::Value *idl) noexcept
    {
        switch (value.type())
        {
        case picarro::types::ValueType::NONE:
            idl->_d() = Picarro::Variant::ValueType::VT_NONE;
            break;

        case picarro::types::ValueType::BOOL:
            idl->value_bool(value.as_bool());
            break;

        case picarro::types::ValueType::UINT:
            idl->value_uint(value.as_uint());
            break;

        case picarro::types::ValueType::SINT:
            idl->value_sint(value.as_sint());
            break;

        case picarro::types::ValueType::REAL:
            idl->value_real(value.as_real());
            break;

        case picarro::types::ValueType::COMPLEX:
            encode(value.as_complex(), &idl->value_complex());
            break;

        case picarro::types::ValueType::CHAR:
            idl->value_char(value.as_char());
            break;

        case picarro::types::ValueType::STRING:
            idl->value_string(value.as_string());
            break;

        case picarro::types::ValueType::BYTEARRAY:
            idl->value_bytearray(value.as_bytearray());
            break;

        case picarro::types::ValueType::TIMEPOINT:
            encode(value.as_timepoint(), &idl->value_timestamp());
            break;

        case picarro::types::ValueType::DURATION:
            encode(value.as_duration(), &idl->value_duration());
            break;

        case picarro::types::ValueType::VALUELIST:
            // idl->value_sequence(
            //     encoded_shared<Picarro::Variant::ValueList>(value.as_valuelist()).list());
            break;

        case picarro::types::ValueType::KVMAP:
            // idl->value_keyvaluemap(
            //     encoded_shared<Picarro::Variant::TaggedValueList>(value.as_kvmap()).list());
            break;

        case picarro::types::ValueType::TVLIST:
            // idl->value_taggedsequence(
            //     encoded_shared<Picarro::Variant::TaggedValueList>(value.as_tvlist()).list());
            break;
        }
    }

    void decode(const Picarro::Variant::Value &idl,
                picarro::types::Value *value) noexcept
    {
        switch (idl._d())
        {
        case Picarro::Variant::ValueType::VT_NONE:
            value->emplace<std::monostate>();
            break;

        case Picarro::Variant::ValueType::VT_BOOL:
            value->emplace<bool>(idl.value_bool());
            break;

        case Picarro::Variant::ValueType::VT_CHAR:
            value->emplace<char>(idl.value_char());
            break;

        case Picarro::Variant::ValueType::VT_UINT:
            value->emplace<picarro::types::largest_uint>(idl.value_uint());
            break;

        case Picarro::Variant::ValueType::VT_SINT:
            value->emplace<picarro::types::largest_sint>(idl.value_sint());
            break;

        case Picarro::Variant::ValueType::VT_REAL:
            value->emplace<double>(idl.value_real());
            break;

        case Picarro::Variant::ValueType::VT_COMPLEX:
            value->emplace<picarro::types::complex>(idl.value_complex().real(), idl.value_complex().imag());
            break;

        case Picarro::Variant::ValueType::VT_STRING:
            value->emplace<std::string>(idl.value_string());
            break;

        case Picarro::Variant::ValueType::VT_BYTEARRAY:
        {
            const auto &sequence = idl.value_bytearray();
            value->emplace<ByteArray>(sequence.cbegin(), sequence.cend());
            break;
        }

        case Picarro::Variant::ValueType::VT_TIMEPOINT:
            value->emplace<picarro::dt::TimePoint>(decoded<picarro::dt::TimePoint>(idl.value_timestamp()));
            break;

        case Picarro::Variant::ValueType::VT_DURATION:
            value->emplace<picarro::dt::Duration>(decoded<picarro::dt::Duration>(idl.value_duration()));
            break;

            // case Picarro::Variant::ValueType::VT_SEQUENCE:
            // {
            //     const auto &sequence = idl.value_sequence();
            //     *value = decoded_shared<picarro::types::ValueList>(
            //         sequence.cbegin(),
            //         sequence.cend());
            //     break;
            // }

            // case Picarro::Variant::ValueType::VT_KEYVALUEMAP:
            // {
            //     const auto &sequence = idl.value_keyvaluemap();
            //     *value = decoded_shared<picarro::types::KeyValueMap>(
            //                  sequence.cbegin(),
            //                  sequence.cend());
            //     break;
            // }

            // case Picarro::Variant::ValueType::VT_TAGGEDSEQUENCE:
            // {
            //     const auto &sequence = idl.value_taggedsequence();
            //     *value = decoded_shared<picarro::types::TaggedValueList>(
            //         sequence.cbegin(),
            //         sequence.cend());
            //     break;
            // }
        }
    }

    //==========================================================================
    // Encode/decode TaggedValue

    void encode(const picarro::types::TaggedValue &native,
                Picarro::Variant::TaggedValue *idl) noexcept
    {
        encode(native.first, native.second, idl);
    }

    void decode(const Picarro::Variant::TaggedValue &idl,
                picarro::types::TaggedValue *native) noexcept
    {
        *native = {idl.tag(), decoded<picarro::types::Value>(idl.value())};
    }

    void encode(const picarro::types::Tag &tag,
                const picarro::types::Value &value,
                Picarro::Variant::TaggedValue *idl) noexcept
    {
        idl->tag(tag.value_or(""));
        idl->value(encoded<Picarro::Variant::Value>(value));
    }

    void decode(const Picarro::Variant::TaggedValue &idl,
                std::string *tag,
                picarro::types::Value *value) noexcept
    {
        *tag = idl.tag();
        decode(idl.value(), value);
    }

    //==========================================================================
    // Encode/decode ValueList

    void encode(const picarro::types::ValueList &native,
                Picarro::Variant::ValueList *idl) noexcept
    {
        idl->list().resize(native.size());
        auto it = idl->list().begin();
        for (const picarro::types::Value &value : native)
        {
            encode(value, &*it++);
        }
    }

    void decode(const Picarro::Variant::ValueList &idl,
                picarro::types::ValueList *native) noexcept
    {
        native->clear();
        native->reserve(idl.list().size());
        for (const auto &idl_value : idl.list())
        {
            decode(idl_value, &native->emplace_back());
        }
    }

    void decode(std::vector<Picarro::Variant::Value>::const_iterator begin,
                std::vector<Picarro::Variant::Value>::const_iterator end,
                picarro::types::ValueList *native) noexcept
    {
        native->clear();
        native->reserve(std::distance(begin, end));
        for (auto it = begin; it != end; it++)
        {
            decode(*it, &native->emplace_back());
        }
    }

    //==========================================================================
    // Encode/decode TaggedValueList

    void encode(const picarro::types::TaggedValueList &native,
                Picarro::Variant::TaggedValueList *idl) noexcept
    {
        idl->list().resize(native.size());
        auto it = idl->list().begin();
        for (const picarro::types::TaggedValue &tv : native)
        {
            encode(tv, &*it++);
        }
    }

    void decode(const Picarro::Variant::TaggedValueList &idl,
                picarro::types::TaggedValueList *native) noexcept
    {
        native->clear();
        native->reserve(idl.list().size());
        for (const Picarro::Variant::TaggedValue &tv : idl.list())
        {
            decode(tv, &native->emplace_back());
        }
    }

    void decode(std::vector<Picarro::Variant::TaggedValue>::const_iterator begin,
                std::vector<Picarro::Variant::TaggedValue>::const_iterator end,
                picarro::types::TaggedValueList *native) noexcept
    {
        native->clear();
        native->reserve(std::distance(begin, end));
        for (auto it = begin; it != end; it++)
        {
            decode(*it, &native->emplace_back());
        }
    }

    //==========================================================================
    // Encode/decode KeyValueMap

    void encode(const picarro::types::KeyValueMap &native,
                Picarro::Variant::TaggedValueList *idl) noexcept
    {
        idl->list().resize(native.size());
        auto it = idl->list().begin();
        for (const auto &[key, value] : native)
        {
            encode(key, value, &*it++);
        }
    }

    void decode(const Picarro::Variant::TaggedValueList &idl,
                picarro::types::KeyValueMap *native) noexcept
    {
        native->clear();
        for (const auto &tv : idl.list())
        {
            decode(tv.value(), &(*native)[tv.tag()]);
        }
    }

}  // namespace picarro::idl
