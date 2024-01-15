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

namespace picarro::idl
{
    //==========================================================================
    // Encode/decode Boolean value

    void encode(bool native,
                Picarro::Shared::BoolValue *idl) noexcept;

    void decode(const Picarro::Shared::BoolValue &idl,
                bool *native) noexcept;

    //==========================================================================
    // Encode/decode Unsigned Integer value

    void encode(picarro::types::largest_uint native,
                Picarro::Shared::UnsignedValue *idl) noexcept;

    void decode(const Picarro::Shared::UnsignedValue &idl,
                picarro::types::largest_uint *native) noexcept;

    //==========================================================================
    // Encode/decode Signed Integer value

    void encode(picarro::types::largest_sint native,
                Picarro::Shared::SignedValue *idl) noexcept;

    void decode(const Picarro::Shared::SignedValue &idl,
                picarro::types::largest_sint *native) noexcept;

    //==========================================================================
    // Encode/decode real value

    void encode(double native,
                Picarro::Shared::RealValue *idl) noexcept;

    void decode(const Picarro::Shared::RealValue &idl,
                double *native) noexcept;

    //==========================================================================
    // Encode/decode Complex value

    void encode(const picarro::types::complex &native,
                Picarro::Shared::ComplexValue *idl) noexcept;

    void decode(const Picarro::Shared::ComplexValue &idl,
                picarro::types::complex *native) noexcept;

    //==========================================================================
    // Encode/decode Timestamp

    void encode(const picarro::dt::TimePoint &native,
                Picarro::Shared::Timestamp *idl) noexcept;

    void decode(const Picarro::Shared::Timestamp &idl,
                picarro::dt::TimePoint *native) noexcept;

    //==========================================================================
    // Encode/decode Duration

    void encode(const picarro::dt::Duration &native,
                Picarro::Shared::Duration *idl) noexcept;

    void decode(const Picarro::Shared::Duration &idl,
                picarro::dt::Duration *native) noexcept;

    //==========================================================================
    // Encode/decode String value

    void encode(std::string native,
                Picarro::Shared::StringValue *idl) noexcept;

    void decode(const Picarro::Shared::StringValue &idl,
                std::string *native) noexcept;

}  // namespace picarro::idl
