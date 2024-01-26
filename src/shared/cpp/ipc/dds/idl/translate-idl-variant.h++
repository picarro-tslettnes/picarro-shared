/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-variant.h++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-common.h++"
#include "variant-types.hpp"  // generated from `variant-types.idl`
#include "types/value.h++"

namespace picarro::idl
{
    //==========================================================================
    // Encode/decode VariantValue

    void encode(const picarro::types::Value &native,
                Picarro::Variant::Value *idl) noexcept;

    void decode(const Picarro::Variant::Value &idl,
                picarro::types::Value *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValue

    void encode(const picarro::types::TaggedValue &native,
                Picarro::Variant::TaggedValue *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValue &idl,
                picarro::types::TaggedValue *native) noexcept;

    void encode(const picarro::types::Tag &tag,
                const picarro::types::Value &value,
                Picarro::Variant::TaggedValue *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValue &idl,
                std::string *tag,
                picarro::types::Value *value) noexcept;

    //==========================================================================
    // Encode/decode ValueList

    void encode(const picarro::types::ValueList &native,
                Picarro::Variant::ValueList *idl) noexcept;

    void decode(const Picarro::Variant::ValueList &idl,
                picarro::types::ValueList *native) noexcept;

    void decode(std::vector<Picarro::Variant::Value>::const_iterator begin,
                std::vector<Picarro::Variant::Value>::const_iterator end,
                picarro::types::ValueList *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValueList

    void encode(const picarro::types::TaggedValueList &native,
                Picarro::Variant::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValueList &idl,
                picarro::types::TaggedValueList *native) noexcept;

    void decode(std::vector<Picarro::Variant::TaggedValue>::const_iterator begin,
                std::vector<Picarro::Variant::TaggedValue>::const_iterator end,
                picarro::types::TaggedValueList *native) noexcept;

    //==========================================================================
    // Encode/decode KeyValueMap

    void encode(const picarro::types::KeyValueMap &native,
                Picarro::Variant::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValueList &idl,
                picarro::types::KeyValueMap *native) noexcept;

}  // namespace picarro::idl
