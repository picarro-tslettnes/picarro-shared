/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-common.c++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-common.h++"  // generated from common_types.idl

namespace picarro::idl
{
    //==========================================================================
    // Encode/decode Boolean value

    void encode(bool native,
                Picarro::Shared::BoolValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Shared::BoolValue &idl,
                bool *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Unsigned Integer value

    void encode(picarro::types::largest_uint native,
                Picarro::Shared::UnsignedValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Shared::UnsignedValue &idl,
                picarro::types::largest_uint *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Signed Integer value

    void encode(picarro::types::largest_sint native,
                Picarro::Shared::SignedValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Shared::SignedValue &idl,
                picarro::types::largest_sint *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode real value

    void encode(double native,
                Picarro::Shared::RealValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Shared::RealValue &idl,
                double *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Complex value

    void encode(const picarro::types::complex &native,
                Picarro::Shared::ComplexValue *idl) noexcept
    {
        idl->real(native.real());
        idl->imag(native.imag());
    }

    void decode(const Picarro::Shared::ComplexValue &idl,
                picarro::types::complex *native) noexcept
    {
        native->real(idl.real());
        native->imag(idl.imag());
    }

    //==========================================================================
    // Encode/decode Timestamp

    void encode(const picarro::dt::TimePoint &native,
                Picarro::Shared::Timestamp *idl) noexcept
    {
        timespec tspec = picarro::dt::to_timespec(native);
        idl->seconds(tspec.tv_sec);
        idl->nanoseconds(tspec.tv_nsec);
    }

    void decode(const Picarro::Shared::Timestamp &idl,
                picarro::dt::TimePoint *native) noexcept
    {
        *native = picarro::dt::to_timepoint(idl.seconds(), idl.nanoseconds());
    }

    //==========================================================================
    // Encode/decode Duration

    void encode(const picarro::dt::Duration &native,
                Picarro::Shared::Duration *idl) noexcept
    {
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(native);
        if (secs > native)
            secs -= std::chrono::seconds(1);
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(native - secs);
        idl->seconds(static_cast<std::uint64_t>(secs.count()));
        idl->nanoseconds(static_cast<std::uint32_t>(nanos.count()));
    }

    void decode(const Picarro::Shared::Duration &idl,
                picarro::dt::Duration *native) noexcept
    {
        *native = std::chrono::duration_cast<picarro::dt::Duration>(
            std::chrono::seconds(idl.seconds()) +
            std::chrono::nanoseconds(idl.nanoseconds()));
    }

    //==========================================================================
    // Encode/decode String value

    void encode(std::string native,
                Picarro::Shared::StringValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Shared::StringValue &idl,
                std::string *native) noexcept
    {
        *native = idl.value();
    }

}  // namespace picarro::idl
