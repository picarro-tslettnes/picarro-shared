/// -*- c++ -*-
//==============================================================================
/// @file zmq-publisher.h++
/// @brief Common functionality wrappers for ZeroMQ publishers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-host.h++"
#include "zmq-filter.h++"
#include "types/bytevector.h++"

#include <thread>
#include <memory>

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
        void publish(const Filter &filter,
                     const types::ByteVector &bytes);
    };

}  // namespace picarro::zmq