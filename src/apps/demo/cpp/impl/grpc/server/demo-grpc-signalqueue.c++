// -*- c++ -*-
//==============================================================================
/// @file demo-grpc-signalqueue.c++
/// @brief connect server-side signals to gRPC streams initiated by clients
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-grpc-signalqueue.h++"
#include "demo-signals.h++"

#include "protobuf-demo-types.h++"

namespace picarro::demo::grpc
{
    void SignalQueue::initialize()
    {
        using Picarro::Demo::Signal;

        this->connect<Greeting>(
            Picarro::Demo::Signal::kGreeting,
            signal_greeting,
            [](const Greeting &greeting, Signal *msg) {
                protobuf::encode(greeting, msg->mutable_greeting());
            });

        this->connect<TimeData>(
            Picarro::Demo::Signal::kTime,
            signal_time,
            [](const TimeData &timedata, Signal *msg) {
                protobuf::encode(timedata, msg->mutable_time());
            });
    }

    void SignalQueue::deinitialize()
    {
        this->disconnect(signal_time);
        this->disconnect(signal_greeting);
    }
}  // namespace picarro::demo::grpc
