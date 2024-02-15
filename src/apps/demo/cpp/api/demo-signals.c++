// -*- c++ -*-
//==============================================================================
/// @file demo-signals.c++
/// @brief Demo App - Internal notification signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

// Application specific modules
#include "demo-signals.h++"

namespace demo
{
    shared::signal::DataSignal<TimeData> signal_time("demo::signal_time");
    shared::signal::MappingSignal<Greeting> signal_greeting("demo::signal_greeting", true);
}  // namespace demo
