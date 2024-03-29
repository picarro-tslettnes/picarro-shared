/// -*- c++ -*-
//==============================================================================
/// @file writer.h++
/// @brief Write values to JSON file
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "json/basewriter.h++"

namespace core::json
{
    class CustomWriter : public BaseWriter
    {
        using This = CustomWriter;
        using Super = BaseWriter;

    public:
        CustomWriter();
        CustomWriter(const fs::path &path);

        void write_stream(std::ostream &stream,
                          const types::Value &value,
                          bool pretty = false) const override;

        std::string encoded(const types::Value &value,
                            bool pretty = false) const override;

    private:
        static std::ostream &to_stream(std::ostream &stream,
                                       const types::Value &value,
                                       bool pretty = false,
                                       const std::string &indent = "");

        static std::ostream &to_stream(std::ostream &stream,
                                       const types::KeyValueMap &kvmap,
                                       bool pretty,
                                       const std::string &indent);

        static std::ostream &to_stream(std::ostream &stream,
                                       const types::ValueList &list,
                                       bool pretty,
                                       const std::string &indent);

        static std::ostream &to_stream(std::ostream &stream,
                                       const types::TaggedValueList &tvlist,
                                       bool pretty,
                                       const std::string &indent);
    };
}  // namespace core::json
