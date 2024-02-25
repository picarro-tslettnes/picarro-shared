/// -*- c++ -*-
//==============================================================================
/// @file settings.h++
/// @brief Global settings instance
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "settingsstore.h++"
#include "platform/init.h++"

#include <memory>

namespace shared
{
    extern std::shared_ptr<shared::SettingsStore> settings;

    void init_settings();
}  // namespace shared
