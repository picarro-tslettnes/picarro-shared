/// -*- c++ -*-
//==============================================================================
/// @file zmq-requester.h++
/// @brief Implements ZeroMQ request/reply pattern - requester
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-satellite.h++"
#include "types/bytevector.h++"

#include <optional>
#include <string>

namespace core::zmq
{
    class Requester : public Satellite
    {
        using This = Requester;
        using Super = Satellite;

    protected:
        Requester(const std::string &host_address,
                  const std::string &channel_name);

    public:
        std::optional<types::ByteVector> send_receive(
            const types::ByteVector &request,
            ::zmq::send_flags send_flags = ::zmq::send_flags::none,
            ::zmq::recv_flags recv_flags = ::zmq::recv_flags::none);
    };

}  // namespace core::zmq
