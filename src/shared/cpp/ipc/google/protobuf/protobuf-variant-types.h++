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

namespace picarro::protobuf
{
    using RepeatedValue = google::protobuf::RepeatedPtrField<Picarro::Variant::Value>;

    //==========================================================================
    // Variant Value encoding/decoding

    void encode(const picarro::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                picarro::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValue encoding/decoding

    void encode(const picarro::types::TaggedValue &tv,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                picarro::types::TaggedValue *tv) noexcept;

    void encode(const picarro::types::Tag &tag,
                const picarro::types::Value &value,
                Picarro::Variant::Value *msg) noexcept;

    void decode(const Picarro::Variant::Value &msg,
                std::string *tag,
                picarro::types::Value *value) noexcept;

    //==========================================================================
    // TaggedValueList encoding/decoding

    /// \brief
    ///    Encode picarro::types::TaggedValueList to Picarro::Variant::ValueList protobuf message
    void encode(const picarro::types::TaggedValueList &tvlist,
                Picarro::Variant::ValueList *msg) noexcept;

    /// \brief
    ///    Decode a Picarro::Variant::Value vector into picarro::types::TaggeValueList.
    void decode(const Picarro::Variant::ValueList &msg,
                picarro::types::TaggedValueList *tvlist) noexcept;

    /// \brief
    ///    Encode picarro::types::TaggedValueList to a repeated Picarro::Variant::Valuef field.
    void encode(const picarro::types::TaggedValueList &tvlist,
                RepeatedValue *msg) noexcept;

    /// \brief
    ///    Decode a repeated Picarro::Variant::Valuef field to TaggedValueList
    void decode(const RepeatedValue &msgs,
                picarro::types::TaggedValueList *tvlist) noexcept;

    //==========================================================================
    // KeyValueMap encoding/decoding

    void encode(const picarro::types::KeyValueMap &map,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                picarro::types::KeyValueMap *map) noexcept;

    void encode(const picarro::types::KeyValueMap &map,
                RepeatedValue *msg) noexcept;

    void decode(const RepeatedValue &msgs,
                picarro::types::KeyValueMap *kvmap) noexcept;

    void encode(const picarro::types::KeyValueMap &map,
                google::protobuf::Map<std::string, Picarro::Variant::Value> *msg) noexcept;

    void decode(const google::protobuf::Map<std::string, Picarro::Variant::Value> &nmsg,
                picarro::types::KeyValueMap *map) noexcept;

    //==========================================================================
    // VariantValueList encoding/decoding

    void encode(const picarro::types::ValueList &list,
                Picarro::Variant::ValueList *msg) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                picarro::types::ValueList *list) noexcept;

    void decode(const RepeatedValue &msgs,
                picarro::types::ValueList *list) noexcept;

    void decode(const Picarro::Variant::ValueList &msg,
                picarro::types::Value *value) noexcept;

}  // namespace picarro::protobuf
