// -*- c++ -*-
//==============================================================================
/// @file demo-api.c++
/// @brief Demo app - Abstract C++ interface
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

// Application specific modules
#include "demo-api.h++"

// Shared modules
#include "string/format.h++"

namespace picarro::demo
{
    //==========================================================================
    /// @class API

    API::API(
        const std::string &identity,
        const std::string &implementation,
        const picarro::dt::TimePoint &birth)
        : identity_(identity),
          implementation_(implementation),
          birth_(birth)
    {
    }

    void API::say_hello(const std::string &text,
                        const picarro::types::KeyValueMap &data)
    {
        this->say_hello(Greeting(text,
                                 this->identity(),
                                 this->implementation(),
                                 this->birth(),
                                 data));
    }

    std::string API::identity() const
    {
        return this->identity_;
    }

    std::string API::implementation() const
    {
        return this->implementation_;
    }

    picarro::dt::TimePoint API::birth() const
    {
        return this->birth_;
    }
}  // namespace picarro::demo
