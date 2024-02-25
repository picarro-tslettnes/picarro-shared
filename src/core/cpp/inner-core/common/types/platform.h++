// -*- c++ -*-
//==============================================================================
/// @file platform.h++
/// @brief Process invocation - Abstract interface
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include <sys/types.h>

#ifdef _MSC_VER
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
typedef unsigned int pid_t;
#else
#include <unistd.h>
#endif
