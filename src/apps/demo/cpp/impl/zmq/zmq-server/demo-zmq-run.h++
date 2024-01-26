// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-run.h++
/// @brief C++ demo - Launch ZeroMQ server implementation
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"
#include "demo-zmq-common.h++"

#include <memory>
#include <string>

namespace picarro::demo::zmq
{
    void run_zmq_service(
        std::shared_ptr<picarro::demo::API> api_provider,
        const std::string &bind_address = {},
        const std::string &channel_name = CHANNEL_NAME);
}
