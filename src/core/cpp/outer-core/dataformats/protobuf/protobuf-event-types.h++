/// -*- c++ -*-
//==============================================================================
/// @file protobuf-event-types.h++
/// @brief Encode/decode routines for common ProtoBuf types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "event_types.pb.h"  // generated from `common-types.proto`
#include "status/event.h++"
#include "status/event.h++"

/// ProtoBuf message conversions.
///
/// These are convenience methods to convert to ("encode...()") or from
/// ("decode...()") "common" ProtoBuf messages (including those defined in
/// "common_types.proto").

namespace protobuf
{
    //==========================================================================
    // status::Domain encoding to/decoding from Picarro::Status::Domain

    void encode(core::status::Domain domain, Picarro::Status::Domain *encoded) noexcept;
    void decode(Picarro::Status::Domain domain, core::status::Domain *decoded) noexcept;

    //==========================================================================
    // core::status::Level encoding to/decoding from Picarro::Status::Level

    void encode(core::status::Level level, Picarro::Status::Level *encoded) noexcept;
    void decode(Picarro::Status::Level level, core::status::Level *decoded) noexcept;

    //==========================================================================
    // core::status::Level encoding to/decoding from Picarro::Status::Level

    void encode(core::status::Flow flow, Picarro::Status::Flow *encoded) noexcept;
    void decode(Picarro::Status::Flow flow, core::status::Flow *decoded) noexcept;

    //==========================================================================
    // core::status::Event encoding to/decoding from Picarro::Status::::EventData

    void encode(const core::status::Event &event, Picarro::Status::Details *msg) noexcept;
    void decode(const Picarro::Status::Details &msg, core::status::Event *event) noexcept;

}  // namespace core::protobuf
