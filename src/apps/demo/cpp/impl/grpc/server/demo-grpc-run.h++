// -*- c++ -*-
//==============================================================================
/// @file demo-grpc-server.h++
/// @brief Demo gRPC server
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"

#include <memory>
#include <string>

namespace picarro::demo::grpc
{
    void run_grpc_service(
        std::shared_ptr<picarro::demo::API> api_provider,
        const std::string &listen_address = {});
}  // namespace picarro::demo::grpc
