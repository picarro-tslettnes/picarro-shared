/// -*- c++ -*-
//==============================================================================
/// @file zmq-pickle-messagebase.h++
/// @brief Base for Python Pickle reader and writer
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "zmq-endpoint.h++"
#include "zmq-filter.h++"

namespace core::zmq
{
    class PyPickleMessageBase
    {
    public:
        PyPickleMessageBase(const std::shared_ptr<Endpoint> &endpoint);
        Filter default_filter();

    protected:
        static Filter pickle_filter(const types::Value &value);

    private:
        Filter default_filter_;
    };

}  // namespace core::zmq
