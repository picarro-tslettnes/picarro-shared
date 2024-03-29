/// -*- c++ -*-
//==============================================================================
/// @file protobuf-signalforwarder.h++
/// @brief Capture server-side signals and encode as ProtoBuf Signal() messages
/// @author Tor Slettnes <tslettnes@picarro.com>
///
/// Class templates for Picarro protobuf services (client and server), including:
///  * Settings store in YourServiceName.json, using JsonCpp as backend
///  * Status/error code wrappers
//==============================================================================

#pragma once
#include "thread/signaltemplate.h++"
#include "signal_types.pb.h"

#include <functional>
#include <unordered_set>

namespace protobuf
{
    //==========================================================================
    /// @brief
    ///    Capture local signals and encode as Protobuf Signal() messages for
    ///    remote peers
    ///
    /// @tparam ProtoT
    ///     ProtoBuf Signal message
    ///

    template <class ProtoT>
    class SignalForwarder
    {
    public:
        // Implementations should override this in order to connect specific
        // Signal<T> or MappingSignal<T> instances to corresponding handlers,
        // which in turn will encode the payload and add the result to this
        // queue.
        virtual void initialize() {}

        // Implementations should override this in order to disconnect any
        // signal handlers that were connected in their `initialize()` method.
        virtual void deinitialize() {}

        // Implementations shold override this to propagate the encoded message
        // to its peers.
        virtual void forward(ProtoT &&message) = 0;

    protected:
        /// @brief
        ///    Create a new Signal message with optional mapping controls.
        static ProtoT create_signal_message(
            core::signal::MappingChange change = core::signal::MAP_NONE,
            const std::string &key = {})
        {
            ProtoT msg;
            msg.set_change(static_cast<Picarro::Signal::MappingChange>(change));
            msg.set_key(key);
            return msg;
        }
    };
}  // namespace protobuf
