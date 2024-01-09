// -*- c++ -*-
//==============================================================================
/// @file demo-grpc-requesthandler.c++
/// @brief Handle DemoService RPC requests
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-grpc-requesthandler.h++"
#include "translate-protobuf-demo.h++"
#include "translate-protobuf-inline.h++"
#include "protobuf-message.h++"
#include "demo-signals.h++"

namespace picarro::demo::grpc
{

    RequestHandler::RequestHandler(const std::shared_ptr<API>& api_provider)
        : provider(api_provider)
    {
        logf_debug("Demo gRPC RequestHandler Constructor");
    }

    ::grpc::Status RequestHandler::say_hello(
        ::grpc::ServerContext* context,
        const ::Picarro::Demo::Greeting* request,
        ::google::protobuf::Empty* response)
    {
        // We received a greeting from a client.  Emit a signal to registered
        // callbacks (slots). (This includes `Publisher::on_signal_greeting()`,
        // which then forwards the signals to clients as a published message.)
        this->provider->say_hello(protobuf::decoded<Greeting>(*request));
        return ::grpc::Status::OK;
    }

    ::grpc::Status RequestHandler::get_current_time(
        ::grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        ::Picarro::Demo::TimeData* response)
    {
        protobuf::encode(this->provider->get_current_time(), response);
        return ::grpc::Status::OK;
    }

    ::grpc::Status RequestHandler::start_ticking(
        ::grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        ::google::protobuf::Empty* response)
    {
        this->provider->start_ticking();
        return ::grpc::Status::OK;
    }

    ::grpc::Status RequestHandler::stop_ticking(
        ::grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        ::google::protobuf::Empty* response)
    {
        this->provider->stop_ticking();
        return ::grpc::Status::OK;
    }

    ::grpc::Status RequestHandler::stream_greetings(
        ::grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        ::grpc::ServerWriter< ::Picarro::Demo::Greeting>* writer)
    {
        return this->connect_stream<Greeting, Picarro::Demo::Greeting, std::string>(
            &signal_greeting,
            [=](signal::MappingChange change,
                const std::string& key,
                const Greeting& greeting,
                Picarro::Demo::Greeting* msg) {
                protobuf::encode(greeting, msg);
            },
            context,
            writer);
    }

    ::grpc::Status RequestHandler::stream_time(
        ::grpc::ServerContext* context,
        const ::google::protobuf::Empty* request,
        ::grpc::ServerWriter< ::Picarro::Demo::TimeData>* writer)
    {
        return this->connect_stream<TimeData, Picarro::Demo::TimeData>(
            &signal_time,
            [=](const TimeData& time,
                Picarro::Demo::TimeData* msg) {
                protobuf::encode(time, msg);
            },
            context,
            writer);
    }
}  // namespace picarro::demo::grpc
