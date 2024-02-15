/// -*- c++ -*-
//==============================================================================
/// @file zmq-pickle-subscriber.h++
/// @brief ZeroMQ subscriber with methods to handle ProtoBuf payloads
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "python-pickle.h++"
#include "zmq-subscriber.h++"

namespace shared::zmq
{
    class PyPickleSubscriber : public Subscriber
    {
        using This = PyPickleSubscriber;
        using Super = Subscriber;

        using Callback = std::function<void(const python::ContainerObject &obj)>;

    protected:
        using Super::Super;

        inline void subscribe(const Callback &callback)
        {
            Super::subscribe([](const types::ByteVector &bytes) {
                callback(python::pickler.unpickle(bytes));
            });
        }
    };

}  // namespace shared::zmq