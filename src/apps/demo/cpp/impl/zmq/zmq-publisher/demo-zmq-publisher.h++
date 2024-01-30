// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-publisher.h++
/// @brief Publish demo signals over ZeroMQ
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-types.h++"
#include "demo-zmq-common.h++"
#include "zmq-protobuf-publisher.h++"

#include "types/create-shared.h++"
#include "thread/signaltemplate.h++"

namespace picarro::demo::zmq
{
    //==========================================================================
    // @class Publisher
    // @brief Publish locally-emitted demo signals over ZeroMQ

    class Publisher : public picarro::zmq::ProtoBufPublisher,
                      public picarro::types::enable_create_shared<Publisher>
    {
        // Convencience alias
        using This = Publisher;
        using Super = picarro::zmq::ProtoBufPublisher;

    protected:
        Publisher(const std::string &bind_address = "",
                  const std::string &channel_name = MESSAGE_CHANNEL);

    public:
        void initialize() override;
        void deinitialize() override;

    private:
        void on_time_update(const TimeData &time_data);

        void on_greeting_update(picarro::signal::MappingChange change,
                                const std::string &identity,
                                const Greeting &greeting);
    };
}  // namespace picarro::demo::zmq
