/// -*- c++ -*-
//==============================================================================
/// @file zmq-publisher.h++
/// @brief Common functionality wrappers for ZeroMQ publishers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-host.h++"
#include "types/bytearray.h++"

#include <thread>

namespace picarro::zmq
{
    class Publisher : public Host
    {
        using This = Publisher;
        using Super = Host;

    protected:
        Publisher(const std::string &bind_address,
                  const std::string &channel_name);

    public:
        void publish(::zmq::message_t &&msg);

        void publish(const types::ByteArray &bytes);

        void publish_with_filter(const types::ByteArray &filter,
                                 const types::ByteArray &bytes);

        void publish_with_topic(const std::string &topic,
                                const types::ByteArray &bytes);
    };

}  // namespace picarro::zmq
