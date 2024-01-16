// -*- c++ -*-
//==============================================================================
/// @file options.c++
/// @brief Parse commmand line options
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"

namespace picarro::demo
{
    Options::Options()
        : Super()
    {
        this->describe("Example server.");
    }

    std::unique_ptr<Options> options;
}  // namespace picarro::demo
