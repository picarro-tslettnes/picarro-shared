// -*- c++ -*-
//==============================================================================
/// @file main.c++
/// @brief Demo service control tool - RTI DDS flavor
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"
#include "demo-dds-client.h++"
#include "demo-provider.h++"
#include "application/init.h++"
#include "logging/logging.h++"

int main(int argc, char** argv)
{
    picarro::application::initialize(argc, argv);

    picarro::demo::options = std::make_unique<picarro::demo::Options>("RTI DDS");
    picarro::demo::options->apply(argc, argv);

    logf_debug("Creating DDS demo provider");
    picarro::demo::provider = picarro::demo::dds::ClientImpl::create_shared(
        picarro::demo::options->identity,
        picarro::demo::options->domain_id);

    logf_debug("Initializing DDS demo provider");
    picarro::demo::provider->initialize();

    bool success = picarro::demo::options->handle_command();

    logf_debug("Deinitializing DDS demo provider");
    picarro::demo::provider->deinitialize();
    picarro::demo::provider.reset();

    picarro::application::deinitialize();
    return success ? 0 : -1;
}
