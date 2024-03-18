// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-signalhandler.h++
/// @brief Subscribe to Demo topics and emit updates locally as signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-protobuf-signalhandler.h++"
#include "types/create-shared.h++"

#include "demo.pb.h"

namespace demo::zmq
{
    class SignalHandler : public core::zmq::ProtoBufSignalHandler<Picarro::Demo::Signal>,
                          public core::types::enable_create_shared<SignalHandler>
    {
        using This = SignalHandler;
        using Super = core::zmq::ProtoBufSignalHandler<Picarro::Demo::Signal>;

    protected:
        void initialize() override;
        void handle_message(const Picarro::Demo::Signal &message) override;
    };

}  // namespace demo::zmq
