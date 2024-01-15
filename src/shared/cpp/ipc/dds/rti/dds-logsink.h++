/// -*- c++ -*-
//==============================================================================
/// @file dds-logsink.h++
/// @brief A logger backed using DDS
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "event-types.hpp"  // generated from `event-types.idl`
#include "dds-publisher.h++"
#include "logging/sinks/messagesink.h++"
#include "types/create-shared.h++"

namespace picarro::logging
{
    class DDSLogger : public MessageSink,
                      public picarro::dds::DDS_Publisher,
                      public picarro::types::enable_create_shared<DDSLogger>
    {
        using This = DDSLogger;
        using Super = MessageSink;

    protected:
        DDSLogger(const std::string &identity, int domain_id);

    protected:
        void open() override;
        void close() override;
        void capture_message(const Message::Ref &msg) override;

    private:
        DataWriterRef<Picarro::Status::LogMessage> log_writer;
    };

}  // namespace picarro::logging
