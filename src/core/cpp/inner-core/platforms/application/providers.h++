/// -*- c++ -*-
//==============================================================================
/// @file providers.h++
/// @brief Superset of platform providers
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include <string>

namespace core::platform
{
    void register_providers(const std::string &exec_name);
    void unregister_providers();
}  // namespace core::platform