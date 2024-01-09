// -*- c++ -*-
//==============================================================================
/// @file client.c++
/// @brief Parse commmand line options for client applications
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "client.h++"

namespace picarro::argparse
{
    //==========================================================================
    // ClientOptions methods

    ClientOptions::ClientOptions()
        : Super(false)
    {
    }

    void ClientOptions::add_options()
    {
        Super::add_options();
        this->add_opt<uint>(
            {"--timeout"},
            "SECONDS",
            "Exit with an error if server is not available after the specified time (default: %default%)",
            &this->timeout,
            30);
    }

}  // namespace picarro::argparse
