/// -*- c++ -*-
//==============================================================================
/// @file windows-symbols.h++
/// @brief Internal symbols - Windows specifics
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "platform/symbols.h++"

namespace picarro::platform
{
    class WindowsSymbolsProvider : public SymbolsProvider
    {
        using This = WindowsSymbolsProvider;
        using Super = SymbolsProvider;

    public:
        WindowsSymbolsProvider();

        std::string cpp_demangle(
            const std::string &abiname,
            bool stem_only) const noexcept override;
    };

}  // namespace picarro::platform
