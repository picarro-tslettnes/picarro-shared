/// -*- c++ -*-
//==============================================================================
/// @file rest-base.h++
/// @brief Implements REST request/reply pattern - base
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "messaging-endpoint.h++"

namespace shared::http
{
    class RESTBase : public messaging::Endpoint
    {
    protected:
        RESTBase(const std::string &endpiont_type,
                 const std::string &service_name);

    protected:
        fs::path settings_file(const std::string &product) const override;

        std::string real_url(
            const std::string &partial_url,
            const std::string &scheme_option = "scheme",
            const std::string &host_option = "host",
            const std::string &port_option = "port",
            const std::string &location_option = "location",
            const std::string &default_scheme = "http",
            const std::string &default_host = "localhost",
            uint default_port = 8000,
            const std::string &default_location = "") const;

    private:
        bool spliturl(
            const std::string &url,
            std::string *scheme,
            std::string *host,
            uint *port,
            std::string *location) const;

        std::string joinurl(
            const std::string &scheme,
            const std::string &host,
            uint port,
            const std::string &location) const;
    };
}  // namespace shared::http