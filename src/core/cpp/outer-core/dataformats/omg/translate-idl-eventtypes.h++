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

namespace idl
{
    //==========================================================================
    // Domain
    void encode(const core::status::Domain &native, Picarro::Status::Domain *idl) noexcept;
    void decode(const Picarro::Status::Domain &idl, core::status::Domain *native) noexcept;

    //==========================================================================
    // Level
    void encode(const core::status::Level &native, Picarro::Status::Level *idl) noexcept;
    void decode(const Picarro::Status::Level &idl, core::status::Level *native) noexcept;

    //==========================================================================
    // Flow
    void encode(const core::status::Flow &native, Picarro::Status::Flow *idl) noexcept;
    void decode(const Picarro::Status::Flow &idl, core::status::Flow *native) noexcept;

    //==========================================================================
    // Event
    void encode(const core::status::Event &native, Picarro::Status::Event *idl) noexcept;
    void decode(const Picarro::Status::Event &idl, core::status::Event *native) noexcept;
    core::status::Event decoded_event(const Picarro::Status::Event &idl) noexcept;

    //==========================================================================
    // LogMessage
    void encode(const core::logging::Message &native, Picarro::Status::LogMessage *idl) noexcept;
    core::logging::Message decoded_logmessage(Picarro::Status::LogMessage idl) noexcept;

}  // namespace idl
