/// -*- c++ -*-
//==============================================================================
/// @file tokenparser-stream.h++
/// @brief JSON token iterator for stream inputs
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "tokenparser-base.h++"

namespace core::json
{
    class StreamParser : public TokenParser
    {
    public:
        StreamParser(std::istream &stream);

        std::size_t token_position() const override;
        std::string token() const override;
        std::string::const_iterator token_begin() const override;
        std::string::const_iterator token_end() const override;

        int getc() override;
        void ungetc(int c) override;
        void init_token(char c) override;
        void append_to_token(char c) override;

    private:
        std::istream &stream_;
        std::string token_;
        std::size_t token_position_;
        std::size_t token_size_;
        std::size_t token_capacity_;
    };
}  // namespace core::json
