/// -*- c++ -*-
//==============================================================================
/// @file convert.c++
/// @brief String conversions
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "string/convert.h++"
#include "string/misc.h++"
#include "platform/symbols.h++"

#include <typeinfo>
#include <unordered_map>
#include <string>

namespace core::str
{
    void checkstream(const std::istream &is,
                     const std::string_view &s,
                     const std::type_info &ti)
    {
        if (is.fail() || !is.eof())
        {
            throw std::invalid_argument(
                str::format("Failed to convert string literal to %s: %r",
                            core::platform::symbols->cpp_demangle(ti.name(), false),
                            s));
        }
    }

    //==========================================================================
    // String-to-string passthrough

    std::string StringConvert<std::string>::from_string(const std::string_view &s)
    {
        return {s.begin(), s.end()};
    }

    std::string StringConvert<std::string>::to_string(const std::string &s)
    {
        return s;
    }

    //==========================================================================
    // Boolean integer conversions

    bool StringConvert<bool>::from_string(const std::string_view &s)
    {
        static const std::regex rxfalse("(?:false|no|off)", std::regex_constants::icase);
        static const std::regex rxtrue("(?:true|yes|on)", std::regex_constants::icase);

        // Check negative words
        if (std::regex_match(s.begin(), s.end(), rxfalse))
        {
            return false;
        }
        // Check positive words
        else if (std::regex_match(s.begin(), s.end(), rxtrue))
        {
            return true;
        }

        try
        {
            return convert_to<std::int64_t>(s) != 0;
        }
        catch (const std::exception &)
        {
        }

        try
        {
            return convert_to<double>(s) != 0.0;
        }
        catch (const std::exception &)
        {
        }

        throw std::invalid_argument(
            str::format("not a boolean value: %r", s));
    }

    std::string StringConvert<bool>::to_string(const bool &value)
    {
        return value ? "true" : "false";
    }


    //==========================================================================
    // Unsigned integer conversions

    // std::uint64_t StringConvert<std::uint64_t>::from_string(const std::string_view &s)
    // {
    //     static const std::errc ok{};
    //     const char *start = &*s.begin();
    //     const char *end = &*s.end();

    //     std::uint64_t value = 0;
    //     // First we try to parse the string as a decimal number
    //     std::cout << "Converting as unsigned decimal" << std::endl;
    //     auto [ptr, ec] = std::from_chars(start, end, value);
    //     if ((ec == ok) && (ptr == end))
    //     {
    //         return value;
    //     }
    //     else
    //     {
    //         // Next, we try to parse it without an explicit base, allowing
    //         // `0x` to indicate hexadecimal. (The reason we didn't do this
    //         // in the first place is that a leading `0` would then be
    //         // considered an octal indicator).
    //         std::cout << "Converting with base 0" << std::endl;
    //         auto [ptr2, ec2] = std::from_chars(start, end, value, 0);
    //         if ((ec2 == ok) && (ptr2 == end))
    //         {
    //             return value;
    //         }
    //         else if (ec != ok)
    //         {
    //             throw std::invalid_argument(std::make_error_code(ec).message());
    //         }
    //         else
    //         {
    //             throw std::invalid_argument(
    //                 str::format("Not all characters converted: %s", s));
    //         }
    //     }
    // }

    // std::string StringConvert<std::uint64_t>::to_string(const std::uint64_t &value)
    // {
    //     std::ostringstream ss;
    //     ss << value;
    //     return ss.str();
    // }

    //==========================================================================
    // Floating point conversions

    // double StringConvert<double>::from_string(const std::string_view &s)
    // {
    //     static const std::errc ok{};
    //     const char *start = &*s.begin();
    //     const char *end = &*s.end();

    //     double value = 0.0;
    //     std::cout << "Converting as real" << std::endl; 
    //     auto [ptr, ec] = std::from_chars(start, end, value);
    //     if (ec != ok)
    //     {
    //         throw std::invalid_argument(std::make_error_code(ec).message());
    //     }
    //     else if (ptr != end)
    //     {
    //         throw std::invalid_argument(
    //             str::format("Not all characters converted: %s", s));
    //     }
    //     return value;
    // }

    // std::string StringConvert<double>::to_string(const double &value)
    // {
    //     std::ostringstream ss;
    //     ss << value;
    //     return ss.str();
    // }

}  // namespace core::str
