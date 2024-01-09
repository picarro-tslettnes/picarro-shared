/// -*- c++ -*-
//==============================================================================
/// @file exceptions.h++
/// @brief Generic exception types, derived from `Error`
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "exception.h++"
#include "error.h++"
#include "platform/symbols.h++"
#include "platform/path.h++"

#include <stdexcept>

namespace picarro::exception
{
    //==========================================================================
    /// @class CustomException
    /// @brief status::Error wrapper for local errors derived on std::exception

    template <class E>
    class CustomException : public Exception<E>
    {
        using Super = Exception<E>;

    public:
        using Super::Super;

        // inline CustomException(status::Domain domain,
        //                        const std::string &origin,
        //                        status::Code code,
        //                        const status::Error::Symbol &symbol,
        //                        const std::string &text,
        //                        const types::KeyValueMap &attributes = {},
        //                        status::Level level = status::Level::FAILED)
        //     : Super({text,         // text
        //                 domain,       // domain
        //                 origin,       // origin
        //                 code,         // code
        //                 symbol,       // symbol
        //                 level,        // level
        //                 {},           // timepoint
        //                 attributes},  // attributes
        //         E(text))
        // {
        // }

        inline CustomException(const status::Error::Symbol &symbol,
                               const std::string &text,
                               const types::KeyValueMap &attributes = {},
                               status::Level level = status::Level::FAILED)
            : Super({text,                         // text
                     status::Domain::APPLICATION,  // domain
                     platform::path->exec_name(),  // origin
                     0,                            // code
                     symbol,                       // symbol
                     level,                        // level
                     {},                           // timepoint
                     attributes})                  // attributes
        {
        }
    };

    //==========================================================================
    /// @class Cancelled
    /// @brief Indicates that an operation was cancelled

    class Cancelled : public CustomException<std::runtime_error>
    {
        using This = Cancelled;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        Cancelled(const std::string &msg = "Cancelled",
                  const std::string &operation = "");
    };

    //==========================================================================
    /// @class Timeout
    /// @brief Indicates that an operation timed out, along with the timeout value.

    class Timeout : public CustomException<std::runtime_error>
    {
        using This = Timeout;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        Timeout(std::string msg, dt::Duration timeout = dt::Duration::zero());
        Timeout(dt::Duration timeout = dt::Duration::zero());
    };

    //==========================================================================
    /// @class InvalidArgument
    /// @brief Indicates an invalid argument value.

    class InvalidArgument : public CustomException<std::invalid_argument>
    {
        using This = InvalidArgument;
        using Super = CustomException<std::invalid_argument>;

    public:
        using Super::Super;

        InvalidArgument(const std::string &msg = "Invalid Argument",
                        const types::Value &argument = {});
    };

    //==========================================================================
    /// @class InvalidLength
    /// @brief Indicates an invalid length specifier

    class InvalidLength : public CustomException<std::length_error>
    {
        using This = InvalidLength;
        using Super = CustomException<std::length_error>;

    public:
        using Super::Super;

        InvalidLength(const std::string &msg = "Invalid Length",
                      uint provided = 0,
                      uint expected = 0);
    };

    /// Indicates not enough arguments were provided
    class MissingArgument : public CustomException<std::length_error>
    {
        using This = MissingArgument;
        using Super = CustomException<std::length_error>;

    public:
        using Super::Super;

        MissingArgument(const std::string &msg = "Missing Argument",
                        uint provided = 0,
                        uint expected = 1);
    };

    /// Indicates too many arguments were provided
    class ExtraneousArgument : public CustomException<std::length_error>
    {
        using This = ExtraneousArgument;
        using Super = CustomException<std::length_error>;

    public:
        using Super::Super;

        ExtraneousArgument(const std::string &msg = "Extraneous Argument",
                           uint provided = 0,
                           uint expected = 0);
    };

    //==========================================================================
    /// @class OutOfRange
    /// @brief Indicates that a out-of-bounds index or missing key

    class OutOfRange : public CustomException<std::out_of_range>
    {
        using This = OutOfRange;
        using Super = CustomException<std::out_of_range>;

    public:
        using Super::Super;

        OutOfRange(const std::string &msg = "Out of range", const types::Value &item = {});
    };

    //==========================================================================
    /// @class NotFound
    /// @brief Indicates that an item was not found (e.g. in a lookup table)

    class NotFound : public CustomException<std::out_of_range>
    {
        using This = NotFound;
        using Super = CustomException<std::out_of_range>;

    public:
        using Super::Super;

        NotFound(const std::string &msg = "Item not found", const types::Value &item = {});
    };

    //==========================================================================
    /// @class Duplicate
    /// @brief Indicates that an item was duplicated

    class Duplicate : public CustomException<std::out_of_range>
    {
        using This = Duplicate;
        using Super = CustomException<std::out_of_range>;

    public:
        using Super::Super;

        Duplicate(const std::string &msg = "Duplicate item",
                  const types::Value &item = {});
    };

    //==========================================================================
    /// @class FailedPrecondition
    /// @brief Indicates that an operation could not proceed

    class FailedPrecondition : public CustomException<std::runtime_error>
    {
        using This = FailedPrecondition;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        FailedPrecondition(const std::string &msg = "Failed Precondition",
                           const types::KeyValueMap &attributes = {});
    };

    //==========================================================================
    /// @class FailedPostcondition
    /// @brief Indicates that an operation could not proceed

    class FailedPostcondition : public CustomException<std::runtime_error>
    {
        using This = FailedPostcondition;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        FailedPostcondition(const std::string &msg = "Failed Postcondition",
                            const types::KeyValueMap &attributes = {});
    };

    //==========================================================================
    /// @class PermissionDenied
    /// @brief Indicates that an item could not be accessed due to missing permissions

    class PermissionDenied : public CustomException<std::runtime_error>
    {
        using This = PermissionDenied;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        PermissionDenied(const std::string &msg = "Permission denied",
                         const std::string &operation = "");
    };

    //==========================================================================
    /// @class ResourceExhausted
    /// @brief Indicates that an operation failed due to lack of system resources

    class ResourceExhausted : public CustomException<std::runtime_error>
    {
        using This = ResourceExhausted;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        ResourceExhausted(const std::string &msg = "Resource exhausted",
                          const std::string &resource = "");
    };

    //==========================================================================
    /// @class Unavailable
    /// @brief Indicates that an resource is currenly unavailable

    class Unavailable : public CustomException<std::runtime_error>
    {
        using This = Unavailable;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        Unavailable(const std::string &msg = "Resource unavailable",
                    const std::string &resource = "");
    };

    //==========================================================================
    /// @class RuntimeError
    /// @brief Indicates that an operation failed

    class RuntimeError : public CustomException<std::runtime_error>
    {
        using This = RuntimeError;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        RuntimeError(const std::string &msg = "Runtime Error",
                     const types::KeyValueMap &attributes = {});
    };

    //==========================================================================
    /// @class UnknownError
    /// @brief Represents an unknown exception

    class UnknownError : public CustomException<std::runtime_error>
    {
        using This = UnknownError;
        using Super = CustomException<std::runtime_error>;

    public:
        using Super::Super;

        UnknownError(const std::string &msg = "Unknown Error",
                     const types::KeyValueMap &attributes = {});
    };

    //==========================================================================
    /// @class SystemError
    /// @brief Error created from a `std::system_error` instance

    class SystemError : public Exception<std::system_error>
    {
        using This = SystemError;
        using Super = Exception<std::system_error>;

    public:
        SystemError(const status::Error &error);
        SystemError(const std::system_error &e);

        explicit SystemError(int errcode, const std::string &what);
        explicit SystemError(int errcode = errno);
        explicit SystemError(const std::string &preamble,
                             int errcode,
                             const std::string &what);

        explicit SystemError(const std::string &preamble, int errcode = errno);
        explicit SystemError(const std::error_category &category,
                             int errorcode,
                             const std::string &what);
    };

    //==========================================================================
    /// @class FilesystemError
    /// @brief Error created from a `std::filesystem_error` instance

    class FilesystemError : public Exception<fs::filesystem_error>
    {
        using This = FilesystemError;
        using Super = Exception<fs::filesystem_error>;

    public:
        FilesystemError(const status::Error &error);

        FilesystemError(const fs::filesystem_error &e);

        explicit FilesystemError(int errcode,
                                 const std::filesystem::path &path1,
                                 const std::filesystem::path &path2,
                                 const std::string &what);
        explicit FilesystemError(int errcode,
                                 const std::filesystem::path &path1,
                                 const std::filesystem::path &path2);
        explicit FilesystemError(int errcode,
                                 const std::filesystem::path &path1,
                                 const std::string &what);
        explicit FilesystemError(int errcode,
                                 const std::filesystem::path &path1);
    };

    //==========================================================================
    /// @class DeviceError
    /// @brief Indicates that a device error occured

    class DeviceError : public Exception<std::runtime_error>
    {
        using This = DeviceError;
        using Super = Exception<std::runtime_error>;

    public:
        using Super::Super;

        DeviceError(const std::string &text,
                    const std::string &device,
                    Code code,
                    const std::string &id,
                    status::Level level,
                    const dt::TimePoint &timepoint = {},
                    const types::KeyValueMap &attributes = {});
    };

    //==========================================================================
    // Map various exceptions to appropriate events

    status::ErrorRef map_to_error(const std::exception &e) noexcept;
    status::ErrorRef map_to_error(std::exception_ptr eptr) noexcept;

};  // namespace picarro::exception

namespace std
{
    /// Define output stream operator "<<" on std::exception and derivatives.
    std::ostream &operator<<(std::ostream &stream, const exception &e);
    std::ostream &operator<<(std::ostream &stream, exception_ptr eptr);
}  // namespace std
