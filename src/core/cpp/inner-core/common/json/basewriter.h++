/// -*- c++ -*-
//==============================================================================
/// @file basewriter.h++
/// @brief JSON writer - abstract interface
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "types/value.h++"
#include "types/filesystem.h++"

#include <fstream>

namespace core::json
{
    class BaseWriter
    {
    public:
        BaseWriter(const std::string &name);

        BaseWriter(const std::string &name,
                   const fs::path &path);

        virtual void write(
            const types::Value &value,
            bool pretty = false);

        virtual void append_file(
            const fs::path &path,
            const types::Value &value,
            bool pretty = false) const;

        virtual void write_file(
            const fs::path &path,
            const types::Value &value,
            bool pretty = false) const;

        virtual void write_stream(
            std::ostream &stream,
            const types::Value &value,
            bool pretty = false) const = 0;

        virtual std::string encoded(
            const types::Value &value,
            bool pretty = false) const = 0;

    public:
        const std::string name;

    private:
        std::unique_ptr<std::ofstream> stream_;
    };
}  // namespace core::json
