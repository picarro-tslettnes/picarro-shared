// -*- c++ -*-
//==============================================================================
/// @file options.c++
/// @brief Parse commmand line options
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"

namespace demo
{
    Options::Options()
        : Super(),
          enable_grpc(false),
          enable_dds(false),
          enable_zmq(false)
    {
        this->describe("Example server.");
    }

    void Options::add_options()
    {
        Super::add_options();

#if USE_GRPC
        this->add_flag(
            {"--grpc", "--enable-grpc"},
            "Enable gRPC service",
            &this->enable_grpc,
            shared::settings->get("enable grpc", true).as_bool());
#endif

#if USE_DDS
        this->add_flag(
            {"--dds", "--enable-dds"},
            "Enable DDS service",
            &this->enable_dds,
            shared::settings->get("enable dds", true).as_bool());
#endif

#if USE_ZMQ
        this->add_flag(
            {"--zmq", "--enable-zmq"},
            "Enable ZeroMQ service",
            &this->enable_zmq,
            shared::settings->get("enable zmq", true).as_bool());
#endif
    }

    std::unique_ptr<Options> options;
}  // namespace demo
