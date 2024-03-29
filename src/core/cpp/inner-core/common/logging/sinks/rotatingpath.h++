/// -*- c++ -*-
//==============================================================================
/// @file rotatingpath.h++
/// @brief Swap log files based on name template
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "chrono/date-time.h++"
#include "types/filesystem.h++"

namespace core::logging
{
    class RotatingPath
    {
        using This = RotatingPath;

    protected:
        RotatingPath(const std::string &path_template,
                     const std::string &default_suffix,
                     const dt::Duration &rotation_interval);

    protected:
        virtual void rotate(const dt::TimePoint &tp);

        std::string path_template() const;
        void check_rotation(const dt::TimePoint &tp);
        dt::TimePoint current_rotation() const;

        fs::path current_path() const;
        fs::path construct_path(const dt::TimePoint &tp) const;
        void update_current_path(const dt::TimePoint &tp);

    private:
        std::string path_template_;
        std::string default_suffix_;
        dt::TimePoint current_rotation_;
        fs::path current_path_;
        dt::Duration rotation_interval_;
        fs::path log_folder_;
        std::string exec_name_;
    };
}  // namespace core::logging
