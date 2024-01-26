/// -*- c++ -*-
//==============================================================================
/// @file zmq-publisher.h++
/// @brief Common functionality wrappers for ZeroMQ publishers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "zmq-publisher.h++"
#include "zmq-filter.h++"

namespace picarro::zmq
{
    Publisher::Publisher(const std::string &bind_address,
                         const std::string &class_name,
                         const std::string &channel_name)
        : Super(bind_address, class_name, channel_name, ::zmq::socket_type::pub)
    {
    }

    std::vector<std::string> Publisher::settings_path() const
    {
        return {MESSAGE_GROUP, "publisher"};
    }

    void Publisher::publish(::zmq::message_t &&msg)
    {
        this->send(std::move(msg), ::zmq::send_flags::dontwait);
    }

    void Publisher::publish(const types::ByteArray &bytes)
    {
        this->send(bytes, ::zmq::send_flags::dontwait);
    }

    void Publisher::publish_with_topic(const std::string &topic,
                                       const types::ByteArray &bytes)
    {
        if (auto filter = Filter::create_from_topic(topic))
        {
            this->send(*filter,
                       ::zmq::send_flags::dontwait | ::zmq::send_flags::sndmore);
        }
        this->send(bytes);
    }

}  // namespace picarro::zmq
