/// -*- c++ -*-
//==============================================================================
/// @file dds-server.h++
/// @brief DDS RPC Server
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "ipc-channel.h++"

#include <dds/rpc/ServerParams.hpp>
#include <dds/rpc/Server.hpp>

namespace picarro::dds
{
    //==========================================================================
    // DDS service Implementation template

    class DDS_Server : public ::dds::rpc::Server,
                       public picarro::ipc::Channel
    {
        // Convencience alias
        using This = DDS_Server;
        using Super = ::dds::rpc::Server;

    public:
        DDS_Server(const std::string &identity, uint thread_pool_size = 4);

    public:
        void initialize();
        void deinitialize();

    private:
        ::dds::rpc::ServerParams server_params(uint thread_pool_size) const;
    };

}  // namespace picarro::dds
