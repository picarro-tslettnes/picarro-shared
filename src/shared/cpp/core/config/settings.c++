/// -*- c++ -*-
//==============================================================================
/// @file settings.c++
/// @brief Global settings instance
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "settings.h++"
#include "status/exceptions.h++"

#include <iostream>

namespace picarro
{
    std::shared_ptr<picarro::SettingsStore> settings;

    void init_settings(const types::PathList &files)
    {
        if (!settings)
        {
            settings = SettingsStore::create_shared();
            try
            {
                settings->load(files);
            }
            catch (const std::exception &e)
            {
                std::cerr << e << std::endl;
            }
        }
    }
}  // namespace picarro
