/// -*- c++ -*-
//==============================================================================
/// @file linux-symbols.c++
/// @brief Functions to produce symbols - Linux verison
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "linux-symbols.h++"

#include <uuid.h>

namespace core::platform
{
    LinuxSymbolsProvider::LinuxSymbolsProvider(const std::string &name)
        : PosixSymbolsProvider(name)
    {
    }

    std::string LinuxSymbolsProvider::uuid() const noexcept
    {
        uuid_t uuid;
        uuid_generate(uuid);

        char buffer[UUID_STR_LEN];
        uuid_unparse(uuid, buffer);
        return buffer;
    }
}  // namespace core::platform
