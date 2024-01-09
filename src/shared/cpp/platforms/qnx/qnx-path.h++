/// -*- c++ -*-
//==============================================================================
/// @file qnx-path.h++
/// @brief Path-related functions - QNX specifics
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "posix-path.h++"

namespace picarro::platform
{
    class QNXPathProvider : public PosixPathProvider
    {
        using This = QNXPathProvider;
        using Super = PosixPathProvider;

    public:
        QNXPathProvider(const std::string &exec_path);
        fs::path exec_path() const noexcept override;
    };

}  // namespace picarro::platform
