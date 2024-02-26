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
    // core::status::Domain encoding to/decoding from Picarro::Status::Domain

    void encode(core::status::Domain domain, Picarro::Status::Domain *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Domain>(domain);
    }

    void decode(Picarro::Status::Domain domain, core::status::Domain *decoded) noexcept
    {
        *decoded = static_cast<core::status::Domain>(domain);
    }

    //==========================================================================
    // core::status::Level encoding to/decoding from Picarro::Status::Level

    void encode(core::status::Level level, Picarro::Status::Level *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Level>(level);
    }

    void decode(Picarro::Status::Level level, core::status::Level *decoded) noexcept
    {
        *decoded = static_cast<core::status::Level>(level);
    }

    //==========================================================================
    // core::status::Flow encoding to/decoding from Picarro::Status::Flow

    void encode(core::status::Flow flow, Picarro::Status::Flow *encoded) noexcept
    {
        *encoded = static_cast<Picarro::Status::Flow>(flow);
    }

    void decode(Picarro::Status::Flow flow, core::status::Flow *decoded) noexcept
    {
        *decoded = static_cast<core::status::Flow>(flow);
    }

    //==========================================================================
    // core::status::Event encoding to/decoding from core::status::Details

    void encode(const core::status::Event &event, Picarro::Status::Details *msg) noexcept
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

    void decode(const Picarro::Status::Details &msg, core::status::Event *event) noexcept
    {
        *event = core::status::Event(
            msg.text(),
            decoded<core::status::Domain>(msg.domain()),
            msg.origin(),
            msg.code(),
            msg.symbol(),
            decoded<core::status::Level>(msg.level()),
            decoded<core::status::Flow>(msg.flow()),
            decoded<core::dt::TimePoint>(msg.timestamp()),
            decoded<core::types::KeyValueMap>(msg.attributes()));
    }

}  // namespace core::protobuf
