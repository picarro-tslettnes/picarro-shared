/// -*- c++ -*-
//==============================================================================
/// @file dds-options-server.h++
/// @brief An option parser with DDS specifics
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "argparse/server.h++"

namespace picarro::argparse
{
    class DDSServiceOptions : public ServerOptions
    {
        using This = DDSServiceOptions;
        using Super = ServerOptions;

    public:
        using Super::Super;

        void add_log_options() override;
        void register_loggers() override;

    private:
        bool log_to_dds;
        bool log_to_dl;
    };

}  // namespace picarro::argparse
