/// -*- c++ -*-
//==============================================================================
/// @file runtime.c++
/// @brief Run-time environment related functions - abstract provider
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "runtime.h++"

namespace shared::platform
{
    ProviderProxy<RunTimeProvider> runtime("runtime environment");
}  // namespace shared::platform
