/// -*- c++ -*-
//==============================================================================
/// @file grpc-signalserver.h++
/// @brief Picarro service provider with signal emitting capability
/// @author Tor Slettnes <tslettnes@picarro.com>
///
/// Class templates for Picarro gRPC services (client and server), including:
///  * Settings store in YourServiceName.json, using JsonCpp as backend
///  * Status/error code wrappers
//==============================================================================

#pragma once
#include "grpc-serverwrapper.h++"
#include "grpc-signalqueue.h++"
#include "protobuf-message.h++"

#include "platform/symbols.h++"

namespace picarro::grpc
{
    //==========================================================================
    /// @class SignalServerWrapper<ServerT>
    /// @brief Server wrapper with signalling interface
    /// @tparam ServiceT
    ///     gRPC service type
    /// @tparam SignalT
    ///     Signal class, derfined in .proto file

    template <class ServiceT>
    class SignalServerWrapper : public ServerWrapper<ServiceT>
    {
        using Super = ServerWrapper<ServiceT>;

    protected:
        using Super::Super;

        // Serve requests to watch for signal changes
        template <class SignalT,
                  class SignalQueueT,
                  class SignalFilterT = Picarro::Signal::Filter>
        inline ::grpc::Status stream_signals(::grpc::ServerContext *cxt,
                                             const SignalFilterT *req,
                                             ::grpc::ServerWriter<SignalT> *writer)
        {
            try
            {
                SignalQueueT queue(*req, platform::symbols->uuid());
                queue.initialize();

                while (true)
                {
                    std::optional<SignalT> msg = queue.get();
                    if (cxt->IsCancelled())
                    {
                        break;
                    }
                    if (msg)
                    {
                        logf_trace("Feeding signal to client %s: %s", cxt->peer(), *msg);
                        writer->Write(*msg);
                    }
                }

                queue.deinitialize();
                return ::grpc::Status::OK;
            }
            catch (...)
            {
                return this->failure(std::current_exception(), *req, cxt->peer());
            }
        }
    };

    template <class ServiceT,
              class SignalT,
              class SignalQueueT,
              class SignalFilterT = Picarro::Signal::Filter>
    class SignalWatchServer : public SignalServerWrapper<ServiceT>
    {
        using Super = SignalServerWrapper<ServiceT>;

    protected:
        using Super::Super;

        // Serve requests to watch for signal changes
        inline ::grpc::Status watch(::grpc::ServerContext *cxt,
                                    const SignalFilterT *req,
                                    ::grpc::ServerWriter<SignalT> *writer) override
        {
            return this->template stream_signals<SignalT, SignalQueueT, SignalFilterT>(
                cxt, req, writer);
        }
    };

}  // namespace picarro::grpc
