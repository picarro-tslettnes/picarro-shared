/// -*- c++ -*-
//==============================================================================
/// @file grpc-signalqueue.h++
/// @brief A blocking queue to propagate signals from SignalServer<> to SignalClient<>
/// @author Tor Slettnes <tslettnes@picarro.com>
///
/// Class templates for Picarro gRPC services (client and server), including:
///  * Settings store in YourServiceName.json, using JsonCpp as backend
///  * Status/error code wrappers
//==============================================================================

#pragma once
#include "protobuf-signalforwarder.h++"
#include "thread/blockingqueue.h++"

namespace picarro::grpc
{
    //==========================================================================
    /// @class SignalQueue<SignalT>
    /// @brief
    ///    Capture and local signals and encode/enqueue as ProtoBuf messages.
    ///
    /// @tparam ProtoT
    ///     Signal class, derfined in .proto file
    ///
    /// Implementations should overwrite the `initialize()` method to connect
    /// specific underlying Signal<T> or MappingSignal<T> instances to a
    /// corresponding handler method, which should then
    ///  * encode its payload of emitted signals to a corresponding protobuf
    ///    Signal() message and
    ///  * override and invoke the pure virtual `forward()` method to propagate
    ///    the encoded message to the remote host.
    /// (The `connect()` method emplate, below, can be used to help with this).
    /// The server's `watch()` method will then stream these messages back to
    /// the client from this queue.
    ///
    /// It is also important to override the `deinitialize()` method to
    /// explicitly disconnect from these same signals, or else the handlers
    /// remain connected to the signal after the client has disconnected and
    /// this SignalForwarder() object has been deleted, which in turn may crash the
    /// server.
    ///
    ///
    /// Each SignalQueue instance represents an active gRPC stream writer, which
    /// in turn is created by the `SignalServiceWrapper::stream_signals()` in
    /// response to a gRPC `watch()` invocation by a client.
    ///
    /// For sample SignalForwarder implementations, see `picarro::demo::SignalForwarder()`

    template <class ProtoT>
    class SignalQueue : public protobuf::SignalForwarder<ProtoT>,
                        public types::BlockingQueue<ProtoT>
    {
    protected:
        using SignalFilter = Picarro::Signal::Filter;

        template <class T>
        using Encoder = std::function<void(T, ProtoT *)>;

        template <class T, class K = std::string>
        using MappingEncoder = std::function<
            void(signal::MappingChange, K, T, ProtoT *)>;

    public:
        SignalQueue(const std::string &id,
                    const SignalFilter &filter,
                    uint maxsize = 0)
            : protobuf::SignalForwarder<ProtoT>(),
              types::BlockingQueue<ProtoT>(maxsize),
              id(id),
              filter_polarity(filter.polarity()),
              filter_indices(filter.indices().begin(), filter.indices().end())
        {
        }

    protected:
        /// @fn connect
        /// @brief Connect a signal of type Signal<T> for encoding/enqueung
        /// @tparam SignalT
        ///    Signal data type
        /// @param[in] signal_index
        ///     Signal enumeration in `.proto` file, do decide whether to actually connect.
        /// @param[in] signal
        ///    Signal to which to connect
        /// @param[in] encoder
        ///    Routine to encode signal data to ProtoBuf Signal message

        template <class SignalT>
        void connect(uint signal_index,
                     signal::Signal<SignalT> &signal,
                     const Encoder<SignalT> &encoder)
        {
            if (this->is_included(signal_index))
            {
                signal.connect(this->id,                  // handle
                               [=](const SignalT &value)  // slot
                               {
                                   ProtoT msg = this->create_signal_message();
                                   encoder(value, &msg);
                                   this->forward(std::move(msg));
                               });
            }
        }

        /// @fn connect
        /// @brief
        ///    Connect a signal of type MappingSignal<T> for encoding/enqueung
        ///    ProtoBuf messages with `change` and `key` fields.
        /// @tparam T
        ///    Signal data type
        /// @param[in] signal_index
        ///     Signal enumeration in .proto file, to decide whether to actually connect.
        /// @param[in] signal
        ///    Signal to which to connect
        /// @param[in] encoder
        ///    Routine to encode signal data to ProtoBuf Signal message

        template <class SignalT>
        void connect(uint signal_index,
                     signal::MappingSignal<SignalT> &signal,
                     const Encoder<SignalT> &encoder)
        {
            if (this->is_included(signal_index))
            {
                signal.connect(
                    this->id,                          // handle
                    [=](signal::MappingChange change,  //
                        const std::string &key,        // slot
                        const SignalT &value)          //
                    {
                        ProtoT msg = this->create_signal_message(change, key);
                        encoder(value, &msg);
                        this->forward(std::move(msg));
                    });
            }
        }

        /// @fn disconnect
        /// @brief Disconnect from a signal
        /// @tparam SignalT
        ///    Signal data tyhpe
        /// @param[in] signal
        ///    Signal from which to disconnect

        template <class SignalT>
        void disconnect(SignalT &signal)
        {
            signal.disconnect(this->id);
        }

        /// @fn forward
        /// @brief
        ///     append encoded signals to this queue for subsequent streaming to client.
        /// @param[in] message
        ////    ProtoBuf `Signal()` message

        void forward(ProtoT &&message) override
        {
            this->put(std::move(message));
        }

    private:
        bool is_included(uint signal_index)
        {
            bool filtered = this->filter_indices.count(signal_index);
            return (filtered == this->filter_polarity);
        }

    protected:
        std::string id;
        bool filter_polarity;
        std::unordered_set<uint> filter_indices;
    };
}  // namespace picarro::grpc

using picarro::grpc::SignalQueue;