/// -*- c++ -*-
//==============================================================================
/// @file symbols.c++
/// @brief Internal symbols - abstract provider
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "symbols.h++"

/// Default filesystem paths.
namespace picarro::platform
{
    ProviderProxy<SymbolsProvider> symbols("symbols");
}  // namespace picarro::platform
