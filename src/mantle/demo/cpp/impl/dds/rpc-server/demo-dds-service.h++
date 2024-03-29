// -*- c++ -*-
//==============================================================================
/// @file demo-dds-service.h++
/// @brief Demo DDS service
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-dds-requesthandler.h++"
#include "dds-service.h++"

namespace demo::dds
{
    //==========================================================================
    // @class Service
    // @brief Handle requests from DemoService clients

    class Service : public core::dds::Service<Picarro::Demo::DemoServiceService>
    {
        using Super = core::dds::Service<Picarro::Demo::DemoServiceService>;

    public:
        Service(const ::dds::rpc::Server &server,
                int domain_id,
                const std::shared_ptr<API> &api);
    };

}  // namespace demo::dds
