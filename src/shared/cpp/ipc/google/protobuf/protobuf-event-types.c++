/// -*- c++ -*-
//==============================================================================
/// @file protobuf-event-types.c++
/// @brief Encode/decode routines for common ProtoBuf types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "protobuf-event-types.h++"
#include "protobuf-standard-types.h++"
#include "protobuf-variant-types.h++"
#include "protobuf-inline.h++"

namespace protobuf
{
    //==========================================================================
    // shared::status::Domain encoding to/decoding from Picarro::Status::Domain

    void encode(shared::status::Domain domain, Picarro::Status::Domain *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Domain>(domain);
    }

    void decode(Picarro::Status::Domain domain, shared::status::Domain *decoded) noexcept
    {
        *decoded = static_cast<shared::status::Domain>(domain);
    }

    //==========================================================================
    // shared::status::Level encoding to/decoding from Picarro::Status::Level

    void encode(shared::status::Level level, Picarro::Status::Level *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Level>(level);
    }

    void decode(Picarro::Status::Level level, shared::status::Level *decoded) noexcept
    {
        *decoded = static_cast<shared::status::Level>(level);
    }

    //==========================================================================
    // shared::status::Flow encoding to/decoding from Picarro::Status::Flow

    void encode(shared::status::Flow flow, Picarro::Status::Flow *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Flow>(flow);
    }

    void decode(Picarro::Status::Flow flow, shared::status::Flow *decoded) noexcept
    {
        *decoded = static_cast<shared::status::Flow>(flow);
    }

    //==========================================================================
    // shared::status::Event encoding to/decoding from shared::status::Details

    void encode(const shared::status::Event &event, Picarro::Status::Details *msg) noexcept
    {
        msg->set_domain(encoded<Picarro::Status::Domain>(event.domain()));
        msg->set_origin(event.origin());
        msg->set_code(event.code());
        msg->set_symbol(event.symbol());
        msg->set_level(encoded<Picarro::Status::Level>(event.level()));
        msg->set_flow(encoded<Picarro::Status::Flow>(event.flow()));
        encode(event.timepoint(), msg->mutable_timestamp());
        encode(event.attributes(), msg->mutable_attributes());
        msg->set_text(event.text());
    }

    void decode(const Picarro::Status::Details &msg, shared::status::Event *event) noexcept
    {
        *event = shared::status::Event(
            msg.text(),
            decoded<shared::status::Domain>(msg.domain()),
            msg.origin(),
            msg.code(),
            msg.symbol(),
            decoded<shared::status::Level>(msg.level()),
            decoded<shared::status::Flow>(msg.flow()),
            decoded<shared::dt::TimePoint>(msg.timestamp()),
            decoded<shared::types::KeyValueMap>(msg.attributes()));
    }

}  // namespace shared::protobuf
