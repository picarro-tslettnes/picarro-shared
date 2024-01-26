// -*- c++ -*-
//==============================================================================
/// @file demo-dds-subscriber.h++
/// @brief Subscribe to Demo topics and emit updates locally as signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-types.hpp"  // Generated from `demo-types.idl`
#include "demo-signals.h++"
#include "dds-subscriber.h++"
#include "types/create-shared.h++"

namespace picarro::demo::dds
{
    //==========================================================================
    /// @class Subscriber
    /// @brief Subscribe to and process updates from demo server
    ///
    /// Received messages are re-emitted locally via
    /// @sa picarro::demo::signal_time and @sa picarro::demo::signal_greeting.

    class Subscriber : public picarro::dds::Subscriber,
                       public picarro::types::enable_create_shared<Subscriber>
    {
        using This = Subscriber;
        using Super = picarro::dds::Subscriber;

    protected:
        Subscriber(const std::string &channel_name, int domain_id);

    private:
        static void on_time_update(
            picarro::signal::MappingChange change,
            const Picarro::Demo::TimeData &time_data);

        static void on_greeting_update(
            picarro::signal::MappingChange change,
            const Picarro::Demo::Greeting &greeting);

    private:
        DataReaderRef<Picarro::Demo::TimeData> time_reader;
        DataReaderRef<Picarro::Demo::Greeting> greeting_reader;
    };

}  // namespace picarro::demo::dds
