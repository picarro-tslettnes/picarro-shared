// -*- c++ -*-
//==============================================================================
/// @file demo-grpc-requesthandler.h++
/// @brief Handle DemoService RPC requests
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"
#include "grpc-signalrequesthandler.h++"

#include "demo_service.grpc.pb.h"  // generated from `demo_service.proto`

#include "types/create-shared.h++"

namespace demo::grpc
{
    //==========================================================================
    // @class RequestHandler
    // @brief Process requests from Demo clients

    class RequestHandler : public core::grpc::SignalRequestHandler<Picarro::Demo::Demo>,
                           public core::types::enable_create_shared<RequestHandler>
    {
        // Convencience aliases
        using This = RequestHandler;
        using Super = core::grpc::SignalRequestHandler<Picarro::Demo::Demo>;

    protected:
        RequestHandler(const std::shared_ptr<API>& api_provider);

    public:
        ::grpc::Status say_hello(
            ::grpc::ServerContext* context,
            const ::Picarro::Demo::Greeting* request,
            ::google::protobuf::Empty* response) override;

        ::grpc::Status get_current_time(
            ::grpc::ServerContext* context,
            const ::google::protobuf::Empty* request,
            ::Picarro::Demo::TimeData* response) override;

        ::grpc::Status start_ticking(
            ::grpc::ServerContext* context,
            const ::google::protobuf::Empty* request,
            ::google::protobuf::Empty* response) override;

        ::grpc::Status stop_ticking(
            ::grpc::ServerContext* context,
            const ::google::protobuf::Empty* request,
            ::google::protobuf::Empty* response) override;

        ::grpc::Status watch(
            ::grpc::ServerContext* context,
            const Picarro::Signal::Filter* request,
            ::grpc::ServerWriter<Picarro::Demo::Signal> *writer) override;

    private:
        std::shared_ptr<API> provider;
    };
}  // namespace demo::grpc
