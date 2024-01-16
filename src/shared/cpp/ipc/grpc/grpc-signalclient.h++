/// -*- c++ -*-
//==============================================================================
/// @file grpc-signalclient.h++
/// @brief Client-side wrapper functionality for Picarro gRPC services
/// @author Tor Slettnes <tslettnes@picarro.com>
///
/// Class templates for Picarro gRPC services (client and server), including:
///  * Settings store in YourServiceName.json, using JsonCpp as backend
///  * Status/error code wrappers
//==============================================================================

#pragma once
#include "grpc-clientwrapper.h++"
#include "thread/binaryevent.h++"
#include "signal_types.pb.h"
#include "protobuf-message.h++"

#include <unordered_set>
#include <set>
#include <functional>

namespace picarro::grpc
{
    //==========================================================================
    /// @class SignalClient<ServiceT, SignalT>
    /// @brief Client wrapper with Signal<T> interface
    /// @tparam ServiceT
    ///     gRPC service type
    /// @tparam SignalT
    ///     Signal class, derfined in .proto file
    ///
    /// This template provides methods to stream back and handle Signal messages
    /// from services with corresponding streaming methods.  A typical .proto
    /// file is expected to contain something like this:
    ///
    /// @code{.proto}
    /// import "signal.proto";
    ///
    /// service MyService
    /// {
    ///     /// Watch for signals from th eserver
    ///     rpc watch (Picarro.Signal.Filter) returns (stream Signal);
    /// }
    ///
    /// message MySignal
    /// {
    ///     oneof signal {
    ///         DataType1 data1 = 8;
    ///         DataType2 data2 = 9;
    ///         ...
    ///     }
    /// }
    /// @endcode
    ///
    ///

    template <class ServiceT, class SignalT>
    class SignalWatchClient : public ClientWrapper<ServiceT>
    {
        using This = SignalWatchClient;
        using Super = ClientWrapper<ServiceT>;

    protected:
        using Callback = std::function<void(const SignalT &signal)>;
        using SignalMap = std::unordered_map<typename SignalT::SignalCase, Callback>;
        using SignalReader = std::unique_ptr<::grpc::ClientReader<SignalT>>;

    protected:
        template <class... Args>
        SignalWatchClient(Args &&...args)
            : Super(std::forward<Args>(args)...),
              watching(false)
        {
        }

        ~SignalWatchClient()
        {
            this->deinitialize();
            this->stop_watching();
        }

    protected:
        /// @brief
        ///     Override in derived classes to set up signal handlers.
        inline virtual void initialize()
        {
            this->addHandler(static_cast<typename SignalT::SignalCase>(0),
                             std::bind(&This::on_init_complete, this));
        }

        inline virtual void deinitialize()
        {
            this->slots.clear();
        }

    protected:
        /// @brief Start watching for signals from server.
        ///
        /// @note
        ///     The server will immediately stream back any signals with the
        ///     `caching` option set to `true`. It is the callers responsibility
        ///     to ensure the corresponding Signal() messages are mapped to
        ///     corresponding signals on the client side before invoking this
        ///     method, so that any initial values are captured.  In other
        ///     words, make the appropriate `addHandler()` invocations prior
        ///     to `start_watching()`.
        ///
        /// @note
        ///     By default the server will connect to and stream back all of its
        ///     known signals.  Use \sa set_signal_filter() to apply a filter.

        inline virtual void start_watching()
        {
            // if (this->slots.empty())
            // {
            //     this->initialize();
            // }

            if (!this->watching)
            {
                this->watching = true;
                this->watch_start = steady::Clock::now();
                this->watch_thread = std::thread(&This::keep_watching, this);
            }
        }

        /// @brief Stop watching for signals from server
        inline void stop_watching()
        {
            this->watching = false;
            this->completionEvent.cancel();

            if (auto cxt = this->watcher_context)
            {
                cxt->TryCancel();
            }

            if (this->watch_thread.joinable())
            {
                this->watch_thread.join();
            }
        }

        /// @brief Add a callback handler for a specific Signal type
        /// @param[in] signalCase
        ///     Enumerated index of a specific signal within the protobuf
        ///     `Signal` message, i.e. its number within the `oneof` clause.
        /// @param[in] callback
        ///     Method that will be invoked to handle corresponding Signal
        ///     messages from the gRPC stream as they are received from the
        ///     server. Normally this method will decode the corresponding field
        ///     from within the message and emit the result as a local Signal or
        ///     MappedSignal within the client process, thereby mirroring the
        ///     original signal that was emitted within the server.
        virtual inline void addHandler(
            typename SignalT::SignalCase signalCase,
            const Callback &callback)
        {
            std::lock_guard lck(this->slots_mtx);
            this->slots.emplace(signalCase, callback);
        }

        /// @brief
        ///    Indicate whether we are currently streaming signals from the server.
        /// @return
        ///    `true` if we are currently streaming signals, `false` otherwise.
        virtual inline bool watching_signals() const
        {
            return this->watching;
        }

        /// @brief
        ///    Block until all cached signals have been received from the server
        /// @param[in] deadline
        ///    Exit if the server cache has not been received within this time.
        /// @return
        ///    `true` if and only if the signal cache was received from the server
        inline bool wait_complete(const steady::TimePoint &deadline)
        {
            return this->completionEvent.wait_until(deadline);
        }

        /// @brief
        ///    Block until all cached signals have been received from the server
        /// @param[in] timeout
        ///    Exit if the server cache has not been received within this duration
        ///    after the last `start_watching()` invocation.
        /// @return
        ///    `true` if and only if the signal cache was received from the server
        inline bool wait_complete(const dt::Duration &timeout)
        {
            return this->wait_complete(
                this->watch_start +
                std::chrono::duration_cast<steady::Duration>(timeout));
        }

    protected:
        virtual inline Picarro::Signal::Filter signal_filter()
        {
            std::lock_guard lck(this->slots_mtx);
            Picarro::Signal::Filter filter;
            filter.set_polarity(true);
            for (const auto &[index, callback] : this->slots)
            {
                filter.add_indices(index);
            }
            return filter;
        }

        virtual inline void handleSignal(const SignalT &msg)
        {
            std::lock_guard lck(this->slots_mtx);
            typename SignalT::SignalCase signalCase = msg.signal_case();
            auto it = this->slots.find(signalCase);
            if (it != this->slots.end())
            {
                (it->second)(msg);
            }
        }

        inline void keep_watching()
        {
            while (this->watching)
            {
                this->watch();
                if (this->watching)
                {
                    logf_notice("Reconnecting to %s at %s",
                                this->servicename(),
                                this->host());
                }
            }
        }

        inline void watch(const Picarro::Signal::Filter &filter)
        {
            SignalT msg;

            auto cxt = this->watcher_context = std::make_shared<::grpc::ClientContext>();
            cxt->set_wait_for_ready(true);

            logf_debug("invoking %s::watch(filter=%s)",
                       this->servicename(),
                       filter);

            try
            {
                SignalReader reader = this->stub->watch(cxt.get(), filter);
                while (reader->Read(&msg))
                {
                    this->handleSignal(msg);
                }

                reader->Finish();
            }
            catch (...)
            {
                logf_notice("%s signal watcher failed: %s",
                            this->servicename(),
                            std::current_exception());
            }

            cxt.reset();
        }

        inline void watch()
        {
            this->watch(this->signal_filter());
        }

        inline void on_init_complete()
        {
            logf_trace("Got completion, setting completionEvent();");
            this->completionEvent.set();
        }

    private:
        bool watching;

    protected:
        steady::TimePoint watch_start;
        SignalMap slots;
        std::mutex slots_mtx;
        std::thread watch_thread;
        std::shared_ptr<::grpc::ClientContext> watcher_context;
        types::BinaryEvent completionEvent;
    };

}  // namespace picarro::grpc