// -*- c++ -*-
//==============================================================================
/// @file demo-native.h++
/// @brief Example app - Local/native implementation
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-api.h++"
#include "types/create-shared.h++"

namespace picarro::demo
{
    class NativeImpl : public API,
                       public picarro::types::enable_create_shared<NativeImpl>
    {
        using This = NativeImpl;
        using Super = API;

    protected:
        NativeImpl(const std::string &identity);

    public:  // Implementation
        void say_hello(const Greeting &greeting) override;
        TimeData get_current_time() override;
        void start_ticking() override;
        void stop_ticking() override;
    };
}  // namespace picarro::demo
