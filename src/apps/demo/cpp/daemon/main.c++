// -*- c++ -*-
//==============================================================================
/// @file main.c++
/// @brief C++ demo - main application
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"           // Command-line options
#include "demo-native.h++"       // Native Example API implementation
#include "application/init.h++"  // Common init routines

#ifdef USE_DDS
#include "demo-dds-server.h++"  // DDS server implementation
#endif

#ifdef USE_GRPC
#include "demo-grpc-server.h++"  // gRPC server implementation
#endif

#include <memory>
#include <thread>

int main(int argc, char** argv)
{
    // Initialize paths, load settings, set up shutdown signal handlers
    picarro::application::initialize(argc, argv);

    picarro::demo::options = std::make_unique<picarro::demo::Options>();
    picarro::demo::options->apply(argc, argv);

    // API provider. In this process we use the native/direct implementation.
    auto api_provider = picarro::demo::NativeImpl::create_shared(
        picarro::demo::options->identity);

    logf_debug("Initializing Demo API provider: %s", api_provider->implementation());
    api_provider->initialize();

    std::list<std::thread> server_threads;

#ifdef USE_GRPC
    if (picarro::demo::options->enable_grpc)
    {
        logf_debug("Spawning gRPC server");
        server_threads.emplace_back(
            picarro::demo::grpc::run_grpc_service,
            api_provider);
    }
#endif

#ifdef USE_DDS
    if (picarro::demo::options->enable_dds)
    {
        logf_debug("Spawning DDS server");
        server_threads.emplace_back(
            picarro::demo::dds::run_dds_service,
            api_provider,
            picarro::demo::options->identity,
            picarro::demo::options->domain_id);
    }
#endif

    for (std::thread& t : server_threads)
    {
        t.join();
    }

    logf_debug("Deinitializing Example API provider: %s", api_provider->implementation());
    api_provider->deinitialize();

    logf_debug("Deinitializing Example application");
    picarro::application::deinitialize();
    return 0;
}
