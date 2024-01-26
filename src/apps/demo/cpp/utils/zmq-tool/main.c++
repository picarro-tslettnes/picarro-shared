// -*- c++ -*-
//==============================================================================
/// @file main.c++
/// @brief Demo service control tool - RTI DDS flavor
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"
#include "demo-zmq-subscriber.h++"
#include "demo-zmq-client.h++"
#include "demo-provider.h++"
#include "status/exceptions.h++"
#include "logging/logging.h++"
#include "application/init.h++"

int main(int argc, char** argv)
{
    picarro::application::initialize(argc, argv);

    picarro::demo::options = std::make_unique<picarro::demo::Options>("ZeroMQ");
    picarro::demo::options->apply(argc, argv);

    auto subscriber = picarro::demo::zmq::Subscriber::create_shared(
        picarro::demo::options->host);

    picarro::demo::provider = picarro::demo::zmq::ClientImpl::create_shared(
        picarro::demo::options->identity,
        picarro::demo::options->host);

    logf_debug("Initializing ZeroMQ demo subscriber");
    subscriber->initialize();

    logf_debug("Initializing ZeroMQ demo provider");
    picarro::demo::provider->initialize();

    bool success = picarro::demo::options->handle_command();

    // Invoke shutdown triggers
    picarro::application::signal_shutdown.emit(0);

    logf_debug("Deinitializing ZeroMQ demo provider");
    picarro::demo::provider->deinitialize();
    picarro::demo::provider.reset();

    logf_debug("Deinitializing ZeroMQ demo subscriber");
    subscriber->deinitialize();
    subscriber.reset();

    logf_debug("Deinitializing application");
    picarro::application::deinitialize();
    return success ? 0 : -1;
}
