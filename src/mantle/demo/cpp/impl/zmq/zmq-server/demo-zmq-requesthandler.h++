// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-requesthandler.h++
/// @brief C++ demo - Invoke handler methods based on ZeroMQ requests
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"
#include "demo-zmq-common.h++"
#include "zmq-protobuf-requesthandler.h++"

#include "demo.pb.h"

#include <memory>

namespace demo::zmq
{
    class RequestHandler : public core::zmq::ProtoBufRequestHandler,
                           public core::types::enable_create_shared<RequestHandler>
    {
        using Super = core::zmq::ProtoBufRequestHandler;

    protected:
        RequestHandler(const std::shared_ptr<API> &api,
                       const std::string interface_name);

        void initialize() override;

        protobuf::Empty say_hello(const Picarro::Demo::Greeting &request);
        Picarro::Demo::TimeData get_current_time(const protobuf::Empty &request);
        protobuf::Empty start_ticking(const protobuf::Empty &);
        protobuf::Empty stop_ticking(const protobuf::Empty &);

    private:
        std::shared_ptr<API> api;

    };

}  // namespace demo::zmq
