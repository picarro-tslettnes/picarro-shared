// -*- c++ -*-
//==============================================================================
/// @file implementations.c++
/// @brief C++ demo - enumerate available implementations
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "implementations.h++"
#include "string/misc.h++"

namespace picarro::demo
{
    picarro::types::SymbolMap<Implementation> implementation_names = {
        {Implementation::NONE, "none"},
        {Implementation::DDS, "dds"},
        {Implementation::GRPC, "grpc"},
        {Implementation::ALL, "all"},
    };

    // Convert from the above enumeration to a string
    std::ostream &operator<<(std::ostream &stream, const Implementation &impl)
    {
        return implementation_names.to_stream(stream, impl);
    }

    // Convert to the above enumeration from a string
    std::istream &operator>>(std::istream &stream, Implementation &impl)
    {
        return implementation_names.from_stream(stream, &impl, Implementation::NONE);
    }
}  // namespace picarro::demo
