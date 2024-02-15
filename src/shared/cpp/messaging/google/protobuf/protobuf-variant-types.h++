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

    void encode(const shared::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                shared::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValue encoding/decoding

    void encode(const shared::types::TaggedValue &tv,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                shared::types::TaggedValue *tv) noexcept;

    void encode(const shared::types::Tag &tag,
                const shared::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                std::string *tag,
                shared::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValueList encoding/decoding

    /// \brief
    ///    Encode shared::types::TaggedValueList to Picarro::Variant::ValueList protobuf message
    void encode(const shared::types::TaggedValueList &tvlist,
                Picarro::Variant::ValueList *msg) noexcept;

    /// \brief
    ///    Decode a Picarro::Variant::Value vector into shared::types::TaggeValueList.
    void decode(const Picarro::Variant::ValueList &msg,
                shared::types::TaggedValueList *tvlist) noexcept;

    /// \brief
    ///    Encode shared::types::TaggedValueList to a repeated Picarro::Variant::Valuef field.
    void encode(const shared::types::TaggedValueList &tvlist,
                RepeatedValue *msg) noexcept;

    /// \brief
    ///    Decode a repeated Picarro::Variant::Valuef field to TaggedValueList
    void decode(const RepeatedValue &msgs,
                shared::types::TaggedValueList *tvlist) noexcept;

    //==========================================================================
    // KeyValueMap encoding/decoding

    void encode(const shared::types::KeyValueMap &map,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                shared::types::KeyValueMap *map) noexcept;

    void encode(const shared::types::KeyValueMap &map,
                RepeatedValue *msg) noexcept;

    void decode(const RepeatedValue &msgs,
                shared::types::KeyValueMap *kvmap) noexcept;

    void encode(const shared::types::KeyValueMap &map,
                google::protobuf::Map<std::string, Picarro::Variant::Value> *msg) noexcept;

    void decode(const google::protobuf::Map<std::string, Picarro::Variant::Value> &nmsg,
                shared::types::KeyValueMap *map) noexcept;

    //==========================================================================
    // VariantValueList encoding/decoding

    void encode(const shared::types::ValueList &list,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                shared::types::ValueList *list) noexcept;

    void decode(const RepeatedValue &msgs,
                shared::types::ValueList *list) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                shared::types::Value *value) noexcept;

}  // namespace shared::protobuf
