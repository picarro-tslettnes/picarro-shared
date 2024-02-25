// -*- c++ -*-
//==============================================================================
/// @file protobuf-demo-types.h++
/// @brief conversions to/from Protocol Buffer messages for Demo application
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "demo-types.h++"
#include "demo_types.pb.h"
#include <ctime>

namespace protobuf
{
    //==========================================================================
    // Greeting
    void encode(const demo::Greeting &greeting, Picarro::Demo::Greeting *msg);
    void decode(const Picarro::Demo::Greeting &msg, demo::Greeting *greeting);

    //==========================================================================
    // TimeData
    void encode(const demo::TimeData &timedata, Picarro::Demo::TimeData *msg);
    void decode(const Picarro::Demo::TimeData &msg, demo::TimeData *timedata);

    //==========================================================================
    // TimeStruct
    void encode(const std::tm &tm, Picarro::Demo::TimeStruct *msg);
    void decode(const Picarro::Demo::TimeStruct &msg, std::tm *tm);
}  // namespace shared::protobuf
