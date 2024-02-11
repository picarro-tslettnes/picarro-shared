// -*- c++ -*-
//==============================================================================
/// @file demo-signals.c++
/// @brief Demo App - Internal notification signals
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

// Application specific modules
#include "demo-signals.h++"

namespace picarro::demo
{
    picarro::signal::Signal<TimeData> signal_time("picarro::demo::signal_time");
    picarro::signal::MappingSignal<Greeting> signal_greeting("picarro::demo::signal_greeting", true);
}  // namespace picarro::demo
