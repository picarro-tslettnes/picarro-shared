/// -*- c++ -*-
//==============================================================================
/// @file filesystem.h++
/// @brief Path-related types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include <vector>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

namespace picarro::types
{
    using PathList = std::vector<fs::path>;
}  // namespace picarro::types

namespace std::filesystem
{
    // Provide output stream operator for some built-in STL types.
    std::ostream &operator<<(std::ostream &stream, const file_type &type);
}  // namespace std::filesystem
