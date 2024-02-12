/// -*- c++ -*-
//==============================================================================
/// @file linux-providers.h++
/// @brief Superset of Linux platform providers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include <string>

namespace shared::platform
{
    void register_linux_providers(const std::string &exec_name);
    void unregister_linux_providers();
}  // namespace shared::platform
