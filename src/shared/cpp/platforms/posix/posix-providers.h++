/// -*- c++ -*-
//==============================================================================
/// @file posix-providers.h++
/// @brief Superset of POSIX platform providers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include <string>

namespace picarro::platform
{
    void register_posix_providers(const std::string &exec_name);
    void unregister_posix_providers();
}  // namespace picarro::platform
