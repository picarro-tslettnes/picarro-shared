/// -*- c++ -*-
//==============================================================================
/// @file http-streambuffer.h++
/// @brief C++ stream interface for data received from HTTP server
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "io/streambuffer.h++"

namespace shared::http
{
    class StreamBuffer : public shared::io::StreamBuffer
    {
    protected:
        int sync() override;
    };
}  // namespace shared::http
