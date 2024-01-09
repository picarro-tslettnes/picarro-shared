// -*- c++ -*-
//==============================================================================
/// @file demo-dds-subscriber.c++
/// @brief Subscribe to Demo topics and emit updates locally as signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

// Application specific modules
#include "demo-dds-subscriber.h++"
#include "translate-idl-demo.h++"

// Shared modules
#include "translate-idl-inline.h++"

// C++ STL modules
#include <functional>

namespace picarro::demo::dds
{
    Subscriber::Subscriber(const std::string &name, int domain_id)
        : Super(name, TYPE_NAME_FULL(Subscriber), domain_id),
          time_reader(this->create_reader<Picarro::Demo::TimeData>(
              Picarro::Demo::TIMEDATA_TOPIC,    // topic_name
              Subscriber::on_time_update,  // handler
              false,                       // reliable
              false)),                     // sync_latest
          greeting_reader(this->create_reader<Picarro::Demo::Greeting>(
              Picarro::Demo::GREETING_TOPIC,        // topic_name
              Subscriber::on_greeting_update,  // handler
              true,                            // reliable
              true))                           // sync_latest
    {
    }

    void Subscriber::on_time_update(picarro::signal::MappingChange change,
                                    const Picarro::Demo::TimeData &time_data)
    {
        // We have received a time update from a remote publisher.
        // Emit this update locally via `picarro::demo::signal_time`, declared in
        // `demo-signals.h++'.
        logf_trace("Received time data %s: %s", change, time_data);
        signal_time.emit(idl::decoded<TimeData>(time_data));
    }

    void Subscriber::on_greeting_update(picarro::signal::MappingChange change,
                                        const Picarro::Demo::Greeting &greeting)
    {
        // We have received a time update from a remote publisher.
        // Emit this update locally via `picarro::demo::signal_time`, declared
        // in `demo-signals.h++'.
        logf_trace("Received greeting %s: %s", change, greeting);
        signal_greeting.emit(change,
                             greeting.identity(),
                             idl::decoded<Greeting>(greeting));
    }
}  // namespace picarro::demo::dds
