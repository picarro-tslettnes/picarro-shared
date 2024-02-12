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
#include "demo-dds-run.h++"  // DDS server implementation
#endif

#ifdef USE_GRPC
#include "demo-grpc-run.h++"  // gRPC server implementation
#endif

#ifdef USE_ZMQ
#include "demo-zmq-run.h++"     // ZeroMQ+ProtoBuf server implementation
#endif

#include <memory>
#include <thread>

int main(int argc, char** argv)
{
    // Initialize paths, load settings, set up shutdown signal handlers
    shared::application::initialize(argc, argv);

    demo::options = std::make_unique<demo::Options>();
    demo::options->apply(argc, argv);

    // API provider. In this process we use the native/direct implementation.
    auto api_provider = demo::NativeImpl::create_shared(
        demo::options->identity);

    logf_debug("Initializing Demo API provider: %s", api_provider->implementation());
    api_provider->initialize();

    std::list<std::thread> server_threads;

#ifdef USE_GRPC
    if (demo::options->enable_grpc)
    {
        logf_debug("Spawning gRPC server");
        server_threads.emplace_back(
            demo::grpc::run_grpc_service,
            api_provider,
            "");
    }
#endif

#ifdef USE_DDS
    if (demo::options->enable_dds)
    {
        logf_debug("Spawning DDS server");
        server_threads.emplace_back(
            demo::dds::run_dds_service,
            api_provider,
            demo::options->identity,
            demo::options->domain_id);
    }
#endif

#ifdef USE_ZMQ
    if (demo::options->enable_zmq)
    {
        log_debug("Spawning ZMQ server");
        server_threads.emplace_back(
            demo::zmq::run_zmq_service,
            api_provider,
            "");
    }
#endif

    for (std::thread& t : server_threads)
    {
        t.join();
    }

    logf_debug("Deinitializing Example API provider: %s", api_provider->implementation());
    api_provider->deinitialize();

    logf_debug("Deinitializing Example application");
    shared::application::deinitialize();
    return 0;
}
