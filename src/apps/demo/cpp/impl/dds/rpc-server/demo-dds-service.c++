// -*- c++ -*-
//==============================================================================
/// @file demo-dds-service.c++
/// @brief Demo DDS service
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-dds-service.h++"
#include "platform/symbols.h++"
#include "logging/logging.h++"

namespace demo::dds
{
    Service::Service(const ::dds::rpc::Server &server,
                     int domain_id,
                     const std::shared_ptr<API> &api_provider)
        : Super(server,
                Picarro::Demo::SERVICE_ID,
                domain_id,
                RequestHandler::create_shared(api_provider))
    {
    }
}  // namespace demo::dds
