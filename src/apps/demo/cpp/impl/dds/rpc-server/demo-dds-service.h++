// -*- c++ -*-
//==============================================================================
/// @file demo-dds-service.h++
/// @brief Demo DDS service
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-dds-requesthandler.h++"
#include "dds-service.h++"

namespace picarro::demo::dds
{
    //==========================================================================
    // @class Service
    // @brief Handle requests from DemoService clients

    class Service
        : public picarro::dds::DDS_Service<Picarro::Demo::DemoServiceService>
    {
        using Super = picarro::dds::DDS_Service<Picarro::Demo::DemoServiceService>;

    public:
        Service(const ::dds::rpc::Server &server,
                int domain_id,
                const std::shared_ptr<API> &api);

        void initialize() override;
        void deinitialize() override;
    };

}  // namespace picarro::demo::dds
