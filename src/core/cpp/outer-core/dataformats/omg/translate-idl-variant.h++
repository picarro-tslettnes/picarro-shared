/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-variant.h++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-common.h++"
#include "variant-types.hpp"  // generated from `variant-types.idl`
#include "types/value.h++"

namespace idl
{
    //==========================================================================
    // Encode/decode VariantValue

    void encode(const core::types::Value &native,
                Picarro::Variant::Value *idl) noexcept;

    void decode(const Picarro::Variant::Value &idl,
                core::types::Value *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValue

    void encode(const core::types::TaggedValue &native,
                Picarro::Variant::TaggedValue *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValue &idl,
                core::types::TaggedValue *native) noexcept;

    void encode(const core::types::Tag &tag,
                const core::types::Value &value,
                Picarro::Variant::TaggedValue *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValue &idl,
                std::string *tag,
                core::types::Value *value) noexcept;

    //==========================================================================
    // Encode/decode ValueList

    void encode(const core::types::ValueList &native,
                Picarro::Variant::ValueList *idl) noexcept;

    void decode(const Picarro::Variant::ValueList &idl,
                core::types::ValueList *native) noexcept;

    void decode(std::vector<Picarro::Variant::Value>::const_iterator begin,
                std::vector<Picarro::Variant::Value>::const_iterator end,
                core::types::ValueList *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValueList

    void encode(const core::types::TaggedValueList &native,
                Picarro::Variant::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValueList &idl,
                core::types::TaggedValueList *native) noexcept;

    void decode(std::vector<Picarro::Variant::TaggedValue>::const_iterator begin,
                std::vector<Picarro::Variant::TaggedValue>::const_iterator end,
                core::types::TaggedValueList *native) noexcept;

    //==========================================================================
    // Encode/decode KeyValueMap

    void encode(const core::types::KeyValueMap &native,
                Picarro::Variant::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Variant::TaggedValueList &idl,
                core::types::KeyValueMap *native) noexcept;

}  // namespace idl
