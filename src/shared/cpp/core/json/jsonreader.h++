/// -*- c++ -*-
//==============================================================================
/// @file jsonreader.h++
/// @brief Read JSON file, possibly with comments
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "jsondecoder.h++"
#include "types/value.h++"
#include "types/filesystem.h++"

namespace shared::json
{
    class JsonReader
    {
        using This = JsonReader;

    public:
        JsonReader(const fs::path &path);

        types::Value read();

        static types::Value read_from(const fs::path &path);

    private:
        static std::string read_text(const fs::path &path);

    private:
        fs::path path_;
    };
}  // namespace shared::json
