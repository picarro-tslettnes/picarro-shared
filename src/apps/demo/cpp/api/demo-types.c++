// -*- c++ -*-
//==============================================================================
/// @file demo-types.c++
/// @brief Example App - common data types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

// Application specific modules
#include "demo-types.h++"

// Shared modules
#include "types/value.h++"
#include "types/partslist.h++"

namespace picarro::demo
{
    //==========================================================================
    /// @class Greeting

    Greeting::Greeting(const std::string &text,
                       const std::string &identity,
                       const std::string &implementation,
                       const picarro::dt::TimePoint &birth,
                       const picarro::types::KeyValueMap &data)
        : text(text),
          identity(identity),
          implementation(implementation),
          birth(birth),
          data(data)
    {
    }

    void Greeting::to_stream(std::ostream &stream) const
    {
        picarro::types::PartsList parts;
        parts.add("text", this->text);
        parts.add("identity", this->identity);
        parts.add("implementation", this->implementation, !this->implementation.empty());
        parts.add("birth", this->birth, this->birth != picarro::dt::TimePoint());
        parts.add("uptime", picarro::dt::Clock::now() - this->birth);
        parts.add("data", this->data, !this->data.empty());
        stream << parts;
    }

    //==========================================================================
    /// @class TimeData
    /// @brief Time representation from the server.

    TimeData::TimeData(const picarro::dt::TimePoint &tp)
        : timepoint(tp),
          localtime(picarro::dt::localtime(tp)),
          utctime(picarro::dt::gmtime(tp))
    {
    }

    TimeData::TimeData(const picarro::dt::TimePoint &tp,
                       const std::tm &localtime,
                       const std::tm &utctime)
        : timepoint(tp),
          localtime(localtime),
          utctime(utctime)
    {
    }

    void TimeData::to_stream(std::ostream &stream) const
    {
        picarro::str::format(stream,
                        "TimeData(epoch=%s, local=%s, utc=%s)",
                        picarro::dt::to_time_t(this->timepoint),
                        picarro::dt::to_string(this->localtime),
                        picarro::dt::to_string(this->utctime));
    }

}  // namespace picarro::demo
