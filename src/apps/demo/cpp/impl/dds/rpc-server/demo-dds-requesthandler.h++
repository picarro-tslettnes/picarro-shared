// -*- c++ -*-
//==============================================================================
/// @file demo-dds-requesthandler.h++
/// @brief Handle DemoService RPC requests
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-interface.hpp"  // generated from `demo-interface.idl`
#include "demo-api.h++"
#include "dds-service.h++"

#include "types/create-shared.h++"

namespace picarro::demo::dds
{
    //==========================================================================
    // @class RequestHandler
    // @brief Process requests from DemoService clients

    class RequestHandler : public Picarro::Demo::DemoService,
                           public picarro::types::enable_create_shared<RequestHandler>
    {
        // Convencience alias
        using This = RequestHandler;
        using Super = Picarro::Demo::DemoService;

    protected:
        RequestHandler(const std::shared_ptr<API> &api_provider);

    public:
        void say_hello(const Picarro::Demo::Greeting &greeting) override;
        Picarro::Demo::TimeData get_current_time() override;
        void start_ticking() override;
        void stop_ticking() override;

    private:
        std::shared_ptr<API> provider;
    };
}  // namespace picarro::demo::dds
