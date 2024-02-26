/// -*- c++ -*-
//==============================================================================
/// @file protobuf-variant-types.h++
/// @brief Encode/decode routines for common ProtoBuf types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "variant_types.pb.h"  // generated from `common-types.proto`
#include "chrono/date-time.h++"
#include "types/value.h++"

/// ProtoBuf message conversions.
///
/// These are convenience methods to convert to ("encode...()") or from
/// ("decode...()") "common" ProtoBuf messages (including those defined in
/// "common_types.proto").

namespace protobuf
{
    using RepeatedValue = google::protobuf::RepeatedPtrField<Picarro::Variant::Value>;

    //==========================================================================
    // Variant Value encoding/decoding

    void encode(const core::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                core::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValue encoding/decoding

    void encode(const core::types::TaggedValue &tv,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                core::types::TaggedValue *tv) noexcept;

    void encode(const core::types::Tag &tag,
                const core::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                std::string *tag,
                core::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValueList encoding/decoding

    /// \brief
    ///    Encode core::types::TaggedValueList to Picarro::Variant::ValueList protobuf message
    void encode(const core::types::TaggedValueList &tvlist,
                Picarro::Variant::ValueList *msg) noexcept;

    /// \brief
    ///    Decode a Picarro::Variant::Value vector into core::types::TaggeValueList.
    void decode(const Picarro::Variant::ValueList &msg,
                core::types::TaggedValueList *tvlist) noexcept;

    /// \brief
    ///    Encode core::types::TaggedValueList to a repeated Picarro::Variant::Valuef field.
    void encode(const core::types::TaggedValueList &tvlist,
                RepeatedValue *msg) noexcept;

    /// \brief
    ///    Decode a repeated Picarro::Variant::Valuef field to TaggedValueList
    void decode(const RepeatedValue &msgs,
                core::types::TaggedValueList *tvlist) noexcept;

    //==========================================================================
    // KeyValueMap encoding/decoding

    void encode(const core::types::KeyValueMap &map,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                core::types::KeyValueMap *map) noexcept;

    void encode(const core::types::KeyValueMap &map,
                RepeatedValue *msg) noexcept;

    void decode(const RepeatedValue &msgs,
                core::types::KeyValueMap *kvmap) noexcept;

    void encode(const core::types::KeyValueMap &map,
                google::protobuf::Map<std::string, Picarro::Variant::Value> *msg) noexcept;

    void decode(const google::protobuf::Map<std::string, Picarro::Variant::Value> &nmsg,
                core::types::KeyValueMap *map) noexcept;

    //==========================================================================
    // VariantValueList encoding/decoding

    void encode(const core::types::ValueList &list,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                core::types::ValueList *list) noexcept;

    void decode(const RepeatedValue &msgs,
                core::types::ValueList *list) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                core::types::Value *value) noexcept;

}  // namespace core::protobuf
