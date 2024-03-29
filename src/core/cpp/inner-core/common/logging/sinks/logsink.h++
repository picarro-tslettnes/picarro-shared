/// -*- c++ -*-
//==============================================================================
/// @file logsink.h++
/// @brief Abstract base for log sinks, derived from `capture::Sink()`
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "sink.h++"
#include "status/event.h++"

#include <string>

namespace core::logging
{
    //==========================================================================
    /// \class LogSink
    /// \brief Base for logging text

    class LogSink : public Sink
    {
        using This = LogSink;
        using Super = Sink;

    public:
        using Ref = std::shared_ptr<LogSink>;

    protected:
        LogSink();

    public:
        bool is_applicable(const types::Loggable &item) const override;
        bool capture(const types::Loggable::Ref &item) override;
        virtual void set_threshold(status::Level threshold);
        status::Level threshold() const;

    protected:
        virtual void capture_event(const status::Event::Ref &event) = 0;

    private:
        status::Level threshold_;
    };
}  // namespace core::logging
