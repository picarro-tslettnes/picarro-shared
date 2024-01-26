// -*- c++ -*-
//==============================================================================
/// @file demo-dds-publisher.h++
/// @brief Publish demo signals over DDS
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-types.hpp"  // generated from `demo-types.idl`
#include "demo-types.h++"
#include "dds-publisher.h++"

#include "types/create-shared.h++"
#include <dds/pub/ddspub.hpp>

namespace picarro::demo::dds
{
    //==========================================================================
    // @class Publisher
    // @brief Publish locally-emitted demo signals over DDS

    class Publisher : public picarro::dds::Publisher,
                      public picarro::types::enable_create_shared<Publisher>
    {
        // Convencience alias
        using This = Publisher;
        using Super = picarro::dds::Publisher;

    protected:
        Publisher(const std::string &channel_name, int domain_id);

    public:
        void initialize() override;
        void deinitialize() override;

    private:
        void on_time_update(const TimeData &time_data);

        void on_greeting_update(picarro::signal::MappingChange change,
                                const std::string &identity,
                                const Greeting &greeting);

    private:
        DataWriterRef<Picarro::Demo::TimeData> time_writer;
        DataWriterRef<Picarro::Demo::Greeting> greeting_writer;
    };
}  // namespace picarro::demo::dds
