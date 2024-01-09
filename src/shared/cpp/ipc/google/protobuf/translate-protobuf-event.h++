/// -*- c++ -*-
//==============================================================================
/// @file translate-protobuf-event.h++
/// @brief Encode/decode routines for common ProtoBuf types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "event_types.pb.h"  // generated from `common-types.proto`
#include "status/event.h++"
#include "status/error.h++"

/// ProtoBuf message conversions.
///
/// These are convenience methods to convert to ("encode...()") or from
/// ("decode...()") "common" ProtoBuf messages (including those defined in
/// "common_types.proto").

namespace picarro::protobuf
{
    //==========================================================================
    // status::Domain encoding to/decoding from Picarro::Status::Domain

    void encode(status::Domain domain, Picarro::Status::Domain *encoded) noexcept;
    void decode(Picarro::Status::Domain domain, status::Domain *decoded) noexcept;

    //==========================================================================
    // status::Level encoding to/decoding from Picarro::Status::Level

    void encode(status::Level level, Picarro::Status::Level *encoded) noexcept;
    void decode(Picarro::Status::Level level, status::Level *decoded) noexcept;

    //==========================================================================
    // status::Event encoding to/decoding from Picarro::Status::::EventData

    void encode(const status::Event &event, Picarro::Status::Details *msg) noexcept;
    void decode(const Picarro::Status::Details &msg, status::Event *event) noexcept;

    //==========================================================================
    // status::Error encoding to/decoding from Picarro::Status::::Details

    void encode(const status::Error &error, Picarro::Status::Details *msg) noexcept;
    void decode(const Picarro::Status::Details &msg, status::Error *error) noexcept;

}  // namespace picarro::protobuf
