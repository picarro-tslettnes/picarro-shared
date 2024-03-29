// -*- c++ -*-
//==============================================================================
/// @file demo-zmq-server.c++
/// @brief C++ demo - Handle ZeroMQ service requests sent as ProtoBuf messages
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-zmq-server.h++"

namespace demo::zmq
{
    Server::Server(const std::shared_ptr<API> &api,
                   const std::string &bind_address,
                   const std::string &channel_name)
        : Super(bind_address,
                channel_name,
                {
                    {DEMO_INTERFACE, RequestHandler::create_shared(api, DEMO_INTERFACE)},
                })
    {
        // std::cerr <<  "Demo Server "
        //           << TYPE_NAME_FULL(This)
        //           << " for channel "
        //           << channel_name
        //           << " constructor."
        //           << std::endl;
    }

}  // namespace demo::zmq
