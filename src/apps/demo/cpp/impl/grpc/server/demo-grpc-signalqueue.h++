// -*- c++ -*-
//==============================================================================
/// @file demo-grpc-signalqueue.h++
/// @brief connect server-side signals to gRPC streams initiated by clients
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-grpc-signalqueue.h++"
#include "demo_service.grpc.pb.h"  // generated from `demo_service.proto`
#include "demo-api.h++"

#include "grpc-signalqueue.h++"

namespace picarro::demo::grpc
{
    //==========================================================================
    /// @class SignalQueue
    /// @brief Connect local signals to a single client over gRPC
    ///
    /// Each SignalQueue instance is associated with a specific invocation of
    /// the server's `watch()` method, and captures signals on the server side
    /// to be streamed back to the client. We connect the desired signals to
    /// corresponding handler methods, which in turn encode the emitted payload
    /// to our own protobuf Signal() message and then appends the result to this
    /// queue, from which they are then streamed back to the client.
    ///
    /// See `service::SignalQueue<T>` for additional info.

    class SignalQueue : public picarro::grpc::SignalQueue<Picarro::Demo::Signal>
    {
        using Super = picarro::grpc::SignalQueue<Picarro::Demo::Signal>;

    public:
        using Super::Super;
        void initialize() override;
        void deinitialize() override;
    };
}  // namespace picarro::demo::grpc
