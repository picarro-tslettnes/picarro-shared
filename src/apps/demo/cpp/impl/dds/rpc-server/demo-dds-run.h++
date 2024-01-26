// -*- c++ -*-
//==============================================================================
/// @file demo-dds-server.h++
/// @brief C++ demo - Launch DDS server implementation
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"

#include <memory>

namespace picarro::demo::dds
{
    void run_dds_service(
        std::shared_ptr<picarro::demo::API> api_provider,
        const std::string &identity,
        int domain_id);
}
