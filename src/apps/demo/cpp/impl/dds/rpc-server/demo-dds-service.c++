// -*- c++ -*-
//==============================================================================
/// @file demo-dds-service.c++
/// @brief Demo DDS service
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-dds-service.h++"
#include "platform/symbols.h++"
#include "logging/logging.h++"

namespace picarro::demo::dds
{
    Service::Service(const ::dds::rpc::Server &server,
                     int domain_id,
                     const std::shared_ptr<API> &api_provider)
        : DDS_Service(server,
                      domain_id,
                      Picarro::Demo::SERVICE_ID,
                      RequestHandler::create_shared(api_provider))
    {
    }

    void Service::initialize()
    {
        logf_debug("Initializing %s", TYPE_NAME_FULL(Service));
        Super::initialize();
    }

    void Service::deinitialize()
    {
        logf_debug("Deinitializing %s", TYPE_NAME_FULL(Service));
        Super::deinitialize();
    }

}  // namespace picarro::demo::dds
