/// -*- c++ -*-
//==============================================================================
/// @file protobuf-event-types.c++
/// @brief Encode/decode routines for common ProtoBuf types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "protobuf-event-types.h++"
#include "protobuf-standard-types.h++"
#include "protobuf-variant-types.h++"
#include "protobuf-inline-types.h++"

namespace picarro::protobuf
{
    //==========================================================================
    // status::Domain encoding to/decoding from Picarro::Status::Domain

    void encode(status::Domain domain, Picarro::Status::Domain *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Domain>(domain);
    }

    void decode(Picarro::Status::Domain domain, status::Domain *decoded) noexcept
    {
        *decoded = static_cast<status::Domain>(domain);
    }

    //==========================================================================
    // status::Level encoding to/decoding from Picarro::Status::Level

    void encode(status::Level level, Picarro::Status::Level *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Level>(level);
    }

    void decode(Picarro::Status::Level level, status::Level *decoded) noexcept
    {
        *decoded = static_cast<status::Level>(level);
    }

    //==========================================================================
    // status::Event encoding to/decoding from status::Details

    void encode(const status::Event &event, Picarro::Status::Details *msg) noexcept
    {
        msg->set_domain(encoded<Picarro::Status::Domain>(event.domain()));
        msg->set_origin(event.origin());
        msg->set_level(encoded<Picarro::Status::Level>(event.level()));
        encode(event.timepoint(), msg->mutable_timestamp());
        encode(event.attributes(), msg->mutable_attributes());
        msg->set_text(event.text());
    }

    void decode(const Picarro::Status::Details &msg, status::Event *event) noexcept
    {
        *event = status::Event(
            msg.text(),
            decoded<status::Domain>(msg.domain()),
            msg.origin(),
            decoded<status::Level>(msg.level()),
            decoded<dt::TimePoint>(msg.timestamp()),
            decoded<types::KeyValueMap>(msg.attributes()));
    }

    //==========================================================================
    // status::Error encoding to/decoding from Picarro::Status::::Details

    void encode(const status::Error &error, Picarro::Status::Details *msg) noexcept
    {
        encode(static_cast<status::Event>(error), msg);
        msg->set_code(error.code());
        msg->set_symbol(error.symbol());
    }

    void decode(const Picarro::Status::Details &msg, status::Error *error) noexcept
    {
        *error = status::Error(
            msg.text(),
            decoded<status::Domain>(msg.domain()),
            msg.origin(),
            msg.code(),
            msg.symbol(),
            decoded<status::Level>(msg.level()),
            decoded<dt::TimePoint>(msg.timestamp()),
            decoded<types::KeyValueMap>(msg.attributes()));
    }

}  // namespace picarro::protobuf
