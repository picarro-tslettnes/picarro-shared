// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-subscriber.h++
/// @brief Subscribe to Demo topics and emit updates locally as signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-protobuf-signalsubscriber.h++"
#include "demo-zmq-common.h++"
#include "types/create-shared.h++"

#include "demo_types.pb.h"

namespace picarro::demo::zmq
{
    //==========================================================================
    /// @class Subscriber
    /// @brief Subscribe to and process updates from demo server
    ///
    /// Received messages are re-emitted locally via
    /// @sa picarro::demo::signal_time and @sa picarro::demo::signal_greeting.

    class Subscriber : public picarro::zmq::ProtoBufSignalSubscriber<Picarro::Demo::Signal>,
                       public picarro::types::enable_create_shared<Subscriber>
    {
        using This = Subscriber;
        using Super = picarro::zmq::ProtoBufSignalSubscriber<Picarro::Demo::Signal>;

    protected:
        Subscriber(const std::string &host_address = "",
                   const std::string &channel_name = MESSAGE_CHANNEL);

    public:
        void initialize() override;
    };

}  // namespace picarro::demo::zmq
