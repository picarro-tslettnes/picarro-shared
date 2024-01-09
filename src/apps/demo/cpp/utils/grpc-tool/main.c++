// -*- c++ -*-
//==============================================================================
/// @file main.c++
/// @brief Demo service control tool - gRPC flavor
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"
#include "demo-grpc-client.h++"
#include "demo-provider.h++"
#include "application/init.h++"
#include "logging/logging.h++"

int main(int argc, char** argv)
{
    picarro::application::initialize(argc, argv);

    picarro::demo::options = std::make_unique<picarro::demo::Options>("gRPC");
    picarro::demo::options->apply(argc, argv);

    logf_debug("Creating gRPC demo provider");
    picarro::demo::provider = picarro::demo::grpc::ClientImpl::create_shared(
        picarro::demo::options->identity);

    logf_debug("Initializing gRPC demo provider");
    picarro::demo::provider->initialize();

    bool success = picarro::demo::options->handle_command();

    logf_debug("Deinitializing gRPC demo provider");
    picarro::demo::provider->deinitialize();
    picarro::demo::provider.reset();

    picarro::application::deinitialize();
    return success ? 0 : -1;
}
