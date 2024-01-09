// -*- c++ -*-
//==============================================================================
/// @file implementations.h++
/// @brief C++ demo - enumerate available implementations
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "types/symbolmap.h++"

#include <map>
#include <iostream>

namespace picarro::demo
{
    enum class Implementation
    {
        NONE,
        DDS,
        GRPC,
        ALL
    };

    extern picarro::types::SymbolMap<Implementation> implementation_names;

    // Convert from the above enumeration to a string
    std::ostream &operator<<(std::ostream &stream, const Implementation &impl);

    // Convert to the above enumeration from a string
    std::istream &operator>>(std::istream &stream, Implementation &impl);
}  // namespace picarro::demo
