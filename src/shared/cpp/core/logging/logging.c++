/// -*- c++ -*-
//==============================================================================
/// @file logging.c++
/// @brief Message capture
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "logging.h++"

namespace picarro::logging
{
    SyncDispatcher message_dispatcher;
    AsyncDispatcher structured_dispatcher;
}
