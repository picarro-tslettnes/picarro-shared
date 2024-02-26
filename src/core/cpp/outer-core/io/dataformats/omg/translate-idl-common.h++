/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-common.h++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "common-types.hpp"  // generated from `common_types.idl`
#include "chrono/date-time.h++"
#include "types/value.h++"

namespace idl
{
    //==========================================================================
    // Encode/decode Boolean value

    void encode(bool native,
                Picarro::Common::BoolValue *idl) noexcept;

    void decode(const Picarro::Common::BoolValue &idl,
                bool *native) noexcept;

    //==========================================================================
    // Encode/decode Unsigned Integer value

    void encode(core::types::largest_uint native,
                Picarro::Common::UnsignedValue *idl) noexcept;

    void decode(const Picarro::Common::UnsignedValue &idl,
                core::types::largest_uint *native) noexcept;

    //==========================================================================
    // Encode/decode Signed Integer value

    void encode(core::types::largest_sint native,
                Picarro::Common::SignedValue *idl) noexcept;

    void decode(const Picarro::Common::SignedValue &idl,
                core::types::largest_sint *native) noexcept;

    //==========================================================================
    // Encode/decode real value

    void encode(double native,
                Picarro::Common::RealValue *idl) noexcept;

    void decode(const Picarro::Common::RealValue &idl,
                double *native) noexcept;

    //==========================================================================
    // Encode/decode Complex value

    void encode(const core::types::complex &native,
                Picarro::Common::ComplexValue *idl) noexcept;

    void decode(const Picarro::Common::ComplexValue &idl,
                core::types::complex *native) noexcept;

    //==========================================================================
    // Encode/decode Timestamp

    void encode(const core::dt::TimePoint &native,
                Picarro::Common::Timestamp *idl) noexcept;

    void decode(const Picarro::Common::Timestamp &idl,
                core::dt::TimePoint *native) noexcept;

    //==========================================================================
    // Encode/decode Duration

    void encode(const core::dt::Duration &native,
                Picarro::Common::Duration *idl) noexcept;

    void decode(const Picarro::Common::Duration &idl,
                core::dt::Duration *native) noexcept;

    //==========================================================================
    // Encode/decode String value

    void encode(std::string native,
                Picarro::Common::StringValue *idl) noexcept;

    void decode(const Picarro::Common::StringValue &idl,
                std::string *native) noexcept;

}  // namespace idl
