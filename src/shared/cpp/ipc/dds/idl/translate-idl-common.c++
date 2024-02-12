/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-common.c++
/// @brief Encode/decode routines for common IDL types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-common.h++"  // generated from common_types.idl

namespace idl
{
    //==========================================================================
    // Encode/decode Boolean value

    void encode(bool native,
                Picarro::Common::BoolValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Common::BoolValue &idl,
                bool *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Unsigned Integer value

    void encode(shared::types::largest_uint native,
                Picarro::Common::UnsignedValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Common::UnsignedValue &idl,
                shared::types::largest_uint *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Signed Integer value

    void encode(shared::types::largest_sint native,
                Picarro::Common::SignedValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Common::SignedValue &idl,
                shared::types::largest_sint *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode real value

    void encode(double native,
                Picarro::Common::RealValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Common::RealValue &idl,
                double *native) noexcept
    {
        *native = idl.value();
    }

    //==========================================================================
    // Encode/decode Complex value

    void encode(const shared::types::complex &native,
                Picarro::Common::ComplexValue *idl) noexcept
    {
        idl->real(native.real());
        idl->imag(native.imag());
    }

    void decode(const Picarro::Common::ComplexValue &idl,
                shared::types::complex *native) noexcept
    {
        native->real(idl.real());
        native->imag(idl.imag());
    }

    //==========================================================================
    // Encode/decode Timestamp

    void encode(const shared::dt::TimePoint &native,
                Picarro::Common::Timestamp *idl) noexcept
    {
        timespec tspec = shared::dt::to_timespec(native);
        idl->seconds(tspec.tv_sec);
        idl->nanoseconds(tspec.tv_nsec);
    }

    void decode(const Picarro::Common::Timestamp &idl,
                shared::dt::TimePoint *native) noexcept
    {
        *native = shared::dt::to_timepoint(idl.seconds(), idl.nanoseconds());
    }

    //==========================================================================
    // Encode/decode Duration

    void encode(const shared::dt::Duration &native,
                Picarro::Common::Duration *idl) noexcept
    {
        auto secs = std::chrono::duration_cast<std::chrono::seconds>(native);
        if (secs > native)
            secs -= std::chrono::seconds(1);
        auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(native - secs);
        idl->seconds(static_cast<std::uint64_t>(secs.count()));
        idl->nanoseconds(static_cast<std::uint32_t>(nanos.count()));
    }

    void decode(const Picarro::Common::Duration &idl,
                shared::dt::Duration *native) noexcept
    {
        *native = std::chrono::duration_cast<shared::dt::Duration>(
            std::chrono::seconds(idl.seconds()) +
            std::chrono::nanoseconds(idl.nanoseconds()));
    }

    //==========================================================================
    // Encode/decode String value

    void encode(std::string native,
                Picarro::Common::StringValue *idl) noexcept
    {
        idl->value(native);
    }

    void decode(const Picarro::Common::StringValue &idl,
                std::string *native) noexcept
    {
        *native = idl.value();
    }

}  // namespace idl
