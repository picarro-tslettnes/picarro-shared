// -*- c++ -*-
//==============================================================================
/// @file demo-dds-client.h++
/// @brief Demo DDS client
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
// Application-specific modules
#include "demo-interface.hpp"  // Generated from `demo-interface.idl`
#include "demo-dds-subscriber.h++"
#include "demo-api.h++"

// Shared modules
#include "dds-client.h++"
#include "types/create-shared.h++"

// 3rd party modules
#include <dds/domain/DomainParticipant.hpp>

namespace picarro::demo::dds
{
    //==========================================================================
    // @class ClientImpl
    // @brief Handle requests from and publish updates to Switchboard clients

    class ClientImpl
        : public API,
          public picarro::dds::DDS_Client_Wrapper<Picarro::Demo::DemoServiceClient>,
          public picarro::types::enable_create_shared<ClientImpl>
    {
        // Convencience alias
        using This = ClientImpl;
        using Super = API;

    protected:
        ClientImpl(const std::string &identity, int domain_id);

    public:
        void initialize() override;

        void say_hello(const Greeting &greeting) override;
        TimeData get_current_time() override;
        void start_ticking() override;
        void stop_ticking() override;

        void start_watching() override;
        void stop_watching() override;

    private:
        std::shared_ptr<Subscriber> subscriber;
    };
}  // namespace picarro::demo::dds
