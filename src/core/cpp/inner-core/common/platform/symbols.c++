/// -*- c++ -*-
//==============================================================================
/// @file symbols.c++
/// @brief Internal symbols - abstract provider
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "symbols.h++"

/// Default filesystem paths.
namespace core::platform
{
    ProviderProxy<SymbolsProvider> symbols("symbols");
}  // namespace core::platform
