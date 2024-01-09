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
                Picarro::Shared::VariantValue *idl) noexcept;

    void decode(const Picarro::Shared::VariantValue &idl,
                picarro::types::Value *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValue

    void encode(const picarro::types::TaggedValue &native,
                Picarro::Shared::TaggedValue *idl) noexcept;

    void decode(const Picarro::Shared::TaggedValue &idl,
                picarro::types::TaggedValue *native) noexcept;

    void encode(const picarro::types::Tag &tag,
                const picarro::types::Value &value,
                Picarro::Shared::TaggedValue *idl) noexcept;

    void decode(const Picarro::Shared::TaggedValue &idl,
                std::string *tag,
                picarro::types::Value *value) noexcept;

    //==========================================================================
    // Encode/decode ValueList

    void encode(const picarro::types::ValueList &native,
                Picarro::Shared::VariantValueList *idl) noexcept;

    void decode(const Picarro::Shared::VariantValueList &idl,
                picarro::types::ValueList *native) noexcept;

    void decode(std::vector<Picarro::Shared::VariantValue>::const_iterator begin,
                std::vector<Picarro::Shared::VariantValue>::const_iterator end,
                picarro::types::ValueList *native) noexcept;

    //==========================================================================
    // Encode/decode TaggedValueList

    void encode(const picarro::types::TaggedValueList &native,
                Picarro::Shared::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Shared::TaggedValueList &idl,
                picarro::types::TaggedValueList *native) noexcept;

    void decode(std::vector<Picarro::Shared::TaggedValue>::const_iterator begin,
                std::vector<Picarro::Shared::TaggedValue>::const_iterator end,
                picarro::types::TaggedValueList *native) noexcept;

    //==========================================================================
    // Encode/decode KeyValueMap

    void encode(const picarro::types::KeyValueMap &native,
                Picarro::Shared::TaggedValueList *idl) noexcept;

    void decode(const Picarro::Shared::TaggedValueList &idl,
                picarro::types::KeyValueMap *native) noexcept;

}  // namespace picarro::idl
