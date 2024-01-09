// -*- c++ -*-
//==============================================================================
/// @file windows-process.h++
/// @brief Process invocation - WINDOWS implementations
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "platform/process.h++"

namespace picarro::platform
{
    /// @brief Process invocation on Linux
    class WindowsProcessProvider : public ProcessProvider
    {
        using This = WindowsProcessProvider;
        using Super = ProcessProvider;

    protected:
        WindowsProcessProvider();

    public:
        PID thread_id() const override;
        PID process_id() const override;
    };

}  // namespace picarro::platform
