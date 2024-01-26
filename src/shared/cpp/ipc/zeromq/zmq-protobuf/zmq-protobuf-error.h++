/// -*- c++ -*-
//==============================================================================
/// @file zmq-protobuf-status.h++
/// @brief Report and process ZMQ invocation status
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "status/event.h++"

#include "request_reply.pb.h"

namespace picarro::zmq
{
    constexpr auto STATUS_FIELD_CODE = "status";

    class ProtoBufError : public status::Event
    {
    public:
        using status::Event::Event;

        ProtoBufError(const Picarro::RR::StatusCode &code,
                      const picarro::status::Event &event);

        Picarro::RR::StatusCode status_code() const;

        std::exception_ptr as_application_error() const override;

        std::string class_name() const noexcept override;
        void populate_fields(types::TaggedValueList *values) const noexcept override;

    private:
        Picarro::RR::StatusCode status_code_;
    };
}  // namespace picarro::zmq
