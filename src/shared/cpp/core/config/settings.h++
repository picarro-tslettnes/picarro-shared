/// -*- c++ -*-
//==============================================================================
/// @file settings.h++
/// @brief Global settings instance
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "settingsstore.h++"
#include "platform/path.h++"

#include <memory>

namespace picarro
{
    extern std::shared_ptr<picarro::SettingsStore> settings;

    void init_settings(const types::PathList &files = {platform::path->exec_name(true), "defaults"});
}  // namespace picarro
