/// -*- c++ -*-
//==============================================================================
/// @file dds-client.h++
/// @brief Mix-in base for DDS client implementations
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "dds-endpoint.h++"
#include "chrono/date-time.h++"
#include "types/create-shared.h++"
#include "logging/logging.h++"
#include "platform/init.h++"

#include <dds/rpc/ClientParams.hpp>

namespace core::dds
{
    //==========================================================================
    // DDS client Implementation template

    template <class BaseClient>
    class Client : public Endpoint,
                   public BaseClient
    {
        using This = Client<BaseClient>;

    public:
        Client(const std::string &service_name, int domain_id)
            : Endpoint("client", service_name, domain_id),
              BaseClient(this->client_params())
        {
        }

    public:
        void initialize() override
        {
            platform::signal_shutdown.connect(
                this->to_string(),
                std::bind(&BaseClient::close, this));
        }

        void deinitialize() override
        {
            platform::signal_shutdown.disconnect(
                this->to_string());
        }

    protected:
        virtual ::dds::rpc::ClientParams client_params() const
        {
            ::dds::rpc::ClientParams params(this->get_participant());
            params.service_name(this->channel_name());
            return params;
        }
    };

    //==========================================================================
    // DDS service Implementation template

    template <class ClientT>
    class Client_Wrapper
    {
    protected:
        Client_Wrapper(const std::string &service_name, int domain_id)
            : client_(service_name, domain_id)
        {
        }

    public:
        inline Client<ClientT> client(
            const steady::Duration &max_wait = std::chrono::seconds(10))
        {
            this->client_.wait_for_service(max_wait);
            return this->client_;
        }

    protected:
        Client<ClientT> client_;
    };

}  // namespace core::dds
