/// -*- c++ -*-
//==============================================================================
/// @file jsonreader.c++
/// @brief Read JSON file, possibly with comments
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "jsonreader.h++"
#include "jsonparser.h++"
#include "status/exceptions.h++"

#include <fstream>

namespace core::json
{
    JsonReader::JsonReader(const fs::path &path)
        : path_(path)
    {
    }

    types::Value JsonReader::read()
    {
        return This::read_from(this->path_);
    }

    types::Value JsonReader::read_from(const fs::path &path)
    {
        return JsonParser::parse_stream(std::ifstream{path});
    }
}  // namespace core::json
