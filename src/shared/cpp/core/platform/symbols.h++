/// -*- c++ -*-
//==============================================================================
/// @file symbols.h++
/// @brief Internal symbols - abstract provider
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "provider.h++"

#define TYPE_NAME_FULL(entity) ::picarro::platform::symbols->cpp_demangle(typeid(entity).name(), false)
#define TYPE_NAME_BASE(entity) ::picarro::platform::symbols->cpp_demangle(typeid(entity).name(), true)

/// Default filesystem paths.
namespace picarro::platform
{
    /// @brief Abstract provider for path-related functions
    class SymbolsProvider : public Provider
    {
        using Super = Provider;

    public:
        // Inherit constructor
        using Super::Super;

        /// @brief Generate a Universally Unique IDentifier
        virtual std::string uuid() const noexcept = 0;

        /// @brief Demangle a type/class name, i.e. `typeid(Class).name`
        virtual std::string cpp_demangle(
            const std::string &abiname,
            bool stem_only) const noexcept = 0;
    };

    /// Global instance, populated with the "best" provider for this system.
    extern ProviderProxy<SymbolsProvider> symbols;

}  // namespace picarro::platform
