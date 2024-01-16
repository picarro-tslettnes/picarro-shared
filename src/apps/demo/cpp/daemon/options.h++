// -*- c++ -*-
//==============================================================================
/// @file options.h++
/// @brief Parse commmand line options
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "argparse/server.h++"

namespace picarro::demo
{
    /// @brief Command-line options for demo service
    ///
    /// @note
    ///    We inherit from `picarro::argparse::ServerOptions` in order to get DDS
    ///    logging capabilities. To build without DDS logging, we could inherit
    ///    directly from `picarro::argparse::ServerOptions`.

    class Options : public picarro::argparse::ServerOptions
    {
        using Super = picarro::argparse::ServerOptions;

    public:
        Options();

    };

    extern std::unique_ptr<Options> options;
}  // namespace picarro::demo
