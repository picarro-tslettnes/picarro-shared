// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-signalwriter.h++
/// @brief Forward local DEMO signals over ZMQ
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-types.h++"
#include "zmq-protobuf-signalwriter.h++"

#include "types/create-shared.h++"

#include "demo.pb.h"

namespace demo::zmq
{
    //==========================================================================
    // @class SignalWriter
    // @brief Connect to local DEMO signals and write via ZMQ

    class SignalWriter : public core::zmq::ProtoBufSignalWriter<Picarro::Demo::Signal>,
                         public core::types::enable_create_shared<SignalWriter>
    {
        // Convencience alias
        using This = SignalWriter;
        using Super = core::zmq::ProtoBufSignalWriter<Picarro::Demo::Signal>;

    protected:
        using Super::Super;

    public:
        void initialize() override;
        void deinitialize() override;
    };
}  // namespace demo::zmq
