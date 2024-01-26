/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-eventtypes.h++
/// @brief Encode/decode routines for common IDL error/status types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "event-types.hpp"  // Generated from `event-types.idl`
#include "status/event.h++"
#include "logging/message/message.h++"
#include "translate-idl-common.h++"
#include "translate-idl-variant.h++"

namespace picarro::idl
{
    //==========================================================================
    // Domain
    void encode(const picarro::status::Domain &native, Picarro::Status::Domain *idl) noexcept;
    void decode(const Picarro::Status::Domain &idl, picarro::status::Domain *native) noexcept;

    //==========================================================================
    // Level
    void encode(const picarro::status::Level &native, Picarro::Status::Level *idl) noexcept;
    void decode(const Picarro::Status::Level &idl, picarro::status::Level *native) noexcept;

    //==========================================================================
    // Flow
    void encode(const picarro::status::Flow &native, Picarro::Status::Flow *idl) noexcept;
    void decode(const Picarro::Status::Flow &idl, picarro::status::Flow *native) noexcept;

    //==========================================================================
    // Event
    void encode(const picarro::status::Event &native, Picarro::Status::Event *idl) noexcept;
    void decode(const Picarro::Status::Event &idl, picarro::status::Event *native) noexcept;
    picarro::status::Event decoded_event(const Picarro::Status::Event &idl) noexcept;

    //==========================================================================
    // LogMessage
    void encode(const picarro::logging::Message &native, Picarro::Status::LogMessage *idl) noexcept;
    picarro::logging::Message decoded_logmessage(Picarro::Status::LogMessage idl) noexcept;

}  // namespace picarro::idl
