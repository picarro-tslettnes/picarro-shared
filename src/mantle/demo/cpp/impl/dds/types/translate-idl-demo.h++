/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-demo.h++
/// @brief Encode/decode routines for Picarro Demo types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "demo-types.hpp"  // Generated from `demo-types.idl`
#include "demo-types.h++"  // Native types
#include "translate-idl-common.h++"
#include "translate-idl-variant.h++"

namespace idl
{
    //==========================================================================
    // Greeting
    void encode(const demo::Greeting &native,
                Picarro::Demo::Greeting *idl);

    void decode(const Picarro::Demo::Greeting &idl,
                demo::Greeting *native);

    //==========================================================================
    // TimeData
    void encode(const demo::TimeData &native,
                Picarro::Demo::TimeData *idl);

    void decode(const Picarro::Demo::TimeData &idl,
                demo::TimeData *native);

    //==========================================================================
    // TimeStruct
    void encode(const std::tm &native,
                Picarro::Demo::TimeStruct *idl);

    void decode(const Picarro::Demo::TimeStruct &idl,
                std::tm *native);

}  // namespace idl
