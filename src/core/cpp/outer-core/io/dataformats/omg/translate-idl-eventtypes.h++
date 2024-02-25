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
    void encode(const shared::status::Domain &native, Picarro::Status::Domain *idl) noexcept;
    void decode(const Picarro::Status::Domain &idl, shared::status::Domain *native) noexcept;

    //==========================================================================
    // Level
    void encode(const shared::status::Level &native, Picarro::Status::Level *idl) noexcept;
    void decode(const Picarro::Status::Level &idl, shared::status::Level *native) noexcept;

    //==========================================================================
    // Flow
    void encode(const shared::status::Flow &native, Picarro::Status::Flow *idl) noexcept;
    void decode(const Picarro::Status::Flow &idl, shared::status::Flow *native) noexcept;

    //==========================================================================
    // Event
    void encode(const shared::status::Event &native, Picarro::Status::Event *idl) noexcept;
    void decode(const Picarro::Status::Event &idl, shared::status::Event *native) noexcept;
    shared::status::Event decoded_event(const Picarro::Status::Event &idl) noexcept;

    //==========================================================================
    // LogMessage
    void encode(const shared::logging::Message &native, Picarro::Status::LogMessage *idl) noexcept;
    shared::logging::Message decoded_logmessage(Picarro::Status::LogMessage idl) noexcept;

}  // namespace idl
