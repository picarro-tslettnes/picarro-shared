/// -*- c++ -*-
//==============================================================================
/// @file zmq-protobuf-signalsubscriber.h++
/// @brief ZeroMQ subscriber with methods to handle ProtoBuf payloads
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-subscriber.h++"
#include "protobuf-signal.h++"

namespace picarro::zmq
{
    template <class SignalT>
    class ProtoBufSignalSubscriber
        : public Subscriber,
          public protobuf::SignalReceiver<SignalT>
    {
        using This = ProtoBufSignalSubscriber;
        using Super = Subscriber;

    protected:
        using Super::Super;

    public:
        void initialize() override
        {
            Subscriber::initialize();
            protobuf::SignalReceiver<SignalT>::initialize();
            this->subscribe([=](const types::ByteArray &bytes) {
                this->process_signal(protobuf::to_message<SignalT>(bytes));
            });
        }

        void deinitialize() override
        {
            this->unsubscribe();
            protobuf::SignalReceiver<SignalT>::deinitialize();
            Subscriber::deinitialize();
        }
    };

}  // namespace picarro::zmq
