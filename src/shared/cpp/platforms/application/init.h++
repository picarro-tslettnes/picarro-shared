// -*- c++ -*-
//==============================================================================
/// @file init.h++
/// @brief Common initialization tasks
//==============================================================================

#pragma once
#include "thread/signaltemplate.h++"

namespace picarro::application
{
    void initialize(int argc, char **argv);
    void deinitialize();

    void shutdown_handler(int signal);

    extern picarro::signal::Signal<int> signal_shutdown;

}  // namespace picarro::application
