/// -*- c++ -*-
//==============================================================================
/// @file exceptions.c++
/// @brief Generic exception types, derived from `Event`
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "exceptions.h++"
#include "platform/path.h++"
#include "types/create-shared.h++"

#include <string.h>

namespace picarro::exception
{
    //==========================================================================
    // Cancelled

    Cancelled::Cancelled(const std::string &msg,
                         const std::string &operation)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"operation", operation}},
                status::Level::WARNING)
    {
    }

    //==========================================================================
    // Timeout

    Timeout::Timeout(std::string msg, dt::Duration timeout)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::ABORTED,
                {{"timeout", timeout}})
    {
    }

    Timeout::Timeout(dt::Duration timeout)
        : Timeout(str::format("Timed out after %s seconds", timeout),
                  timeout)
    {
    }

    //==========================================================================
    // InvalidArgument

    InvalidArgument::InvalidArgument(const std::string &msg,
                                     const types::Value &argument)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"argument", argument}})
    {
    }

    //==========================================================================
    // InvalidLength

    InvalidLength::InvalidLength(const std::string &msg,
                                 uint provided,
                                 uint expected)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"provided", provided},
                 {"expected", expected}})
    {
    }

    //==========================================================================
    // MissingArgument

    MissingArgument::MissingArgument(const std::string &msg,
                                     uint provided,
                                     uint expected)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"provided", provided},
                 {"expected", expected}})
    {
    }

    //==========================================================================
    // ExtraneousArgument

    ExtraneousArgument::ExtraneousArgument(const std::string &msg,
                                           uint provided,
                                           uint expected)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"provided", provided},
                 {"expected", expected}})
    {
    }

    //==========================================================================
    // OutOfRange

    OutOfRange::OutOfRange(const std::string &msg,
                           const types::Value &item)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"item", item}})
    {
    }

    //==========================================================================
    // FailedPrecondition

    FailedPrecondition::FailedPrecondition(const std::string &msg,
                                           const types::KeyValueMap &attributes)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                attributes)
    {
    }

    //==========================================================================
    // FailedPostcondition

    FailedPostcondition::FailedPostcondition(const std::string &msg,
                                             const types::KeyValueMap &attributes)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::ABORTED,
                attributes)
    {
    }

    //==========================================================================
    // NotFound

    NotFound::NotFound(const std::string &msg,
                       const types::Value &item)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"item", item}})
    {
    }

    //==========================================================================
    // Duplicate

    Duplicate::Duplicate(const std::string &msg,
                         const types::Value &item)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"item", item}})
    {
    }

    //==========================================================================
    // PermissionDenied

    PermissionDenied::PermissionDenied(const std::string &msg,
                                       const std::string &operation)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"operation", operation}})
    {
    }

    //==========================================================================
    // ResourceExhausted

    ResourceExhausted::ResourceExhausted(const std::string &msg,
                                         const std::string &resource)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::ABORTED,
                {{"resource", resource}})
    {
    }

    //==========================================================================
    // Unavailable

    Unavailable::Unavailable(const std::string &msg,
                             const std::string &resource)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::CANCELLED,
                {{"resource", resource}})
    {
    }

    //==========================================================================
    // RuntimeError

    RuntimeError::RuntimeError(const std::string &msg,
                               const types::KeyValueMap &attributes)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::ABORTED,
                attributes)
    {
    }

    //==========================================================================
    // UnknownError

    UnknownError::UnknownError(const std::string &msg,
                               const types::KeyValueMap &attributes)
        : Super(TYPE_NAME_BASE(This),
                msg,
                status::Flow::ABORTED,
                attributes)
    {
    }

    //==========================================================================
    // SystemError

    SystemError::SystemError(const status::Event &event)
        : Super(event,
                std::system_error(
                    std::error_code(event.code(), std::generic_category()),
                    event.text()))
    {
    }

    SystemError::SystemError(const std::system_error &e)
        : Super({e.what(),                    // text
                 status::Domain::SYSTEM,      // domain
                 e.code().category().name(),  // origin
                 e.code().value(),            // code
                 {},                          // id
                 status::Level::FAILED,       // level
                 status::Flow::ABORTED,       // flow
                 {},                          // timepoint
                 {}},                         // attributes
                std::system_error(e))
    {
    }

    SystemError::SystemError(int errcode,
                             const std::string &what)
        : SystemError(
              std::system_error(
                  std::error_code(static_cast<int>(errcode), std::generic_category()),
                  what))
    {
    }

    SystemError::SystemError(int errcode)
        : SystemError(errcode, strerror(errcode))
    {
    }

    SystemError::SystemError(const std::string &preamble,
                             int errcode,
                             const std::string &what)
        : SystemError(errcode, str::format("%s: %s", preamble, what))
    {
    }

    SystemError::SystemError(const std::string &preamble, int errcode)
        : SystemError(preamble, errcode, strerror(errcode))
    {
    }

    SystemError::SystemError(const std::error_category &category,
                             int errorcode,
                             const std::string &what)
        : SystemError(std::system_error(errorcode, category, what))
    {
    }

    //==========================================================================
    /// @class FilesystemError
    /// @brief Error created from a `std::filesystem_error` instance

    FilesystemError::FilesystemError(const Event &event)
        : Super(event,
                fs::filesystem_error(
                    event.text(),
                    event.attribute("path1").as_string(),
                    event.attribute("path2").as_string(),
                    std::error_code(static_cast<int>(event.code()),
                                    std::system_category())))
    {
    }

    FilesystemError::FilesystemError(const fs::filesystem_error &e)
        : Super({e.what(),                    // text
                 status::Domain::SYSTEM,      // domain
                 e.code().category().name(),  // origin
                 e.code().value(),            // code
                 TYPE_NAME_BASE(This),        // id
                 status::Level::FAILED,       // level
                 status::Flow::ABORTED,       // flow
                 {},                          // timepoint
                 {                            // attributes
                  {"path1", types::Value(e.path1().string())},
                  {"path2", types::Value(e.path2().string())}}},
                fs::filesystem_error(e))
    {
    }

    FilesystemError::FilesystemError(int errcode,
                                     const std::filesystem::path &path1,
                                     const std::filesystem::path &path2,
                                     const std::string &what)
        : FilesystemError(fs::filesystem_error(
              what,
              path1,
              path2,
              std::error_code(static_cast<int>(errcode), std::system_category())))
    {
    }

    FilesystemError::FilesystemError(int errcode,
                                     const std::filesystem::path &path1,
                                     const std::filesystem::path &path2)
        : FilesystemError(errcode, path1, path2, strerror(errcode))
    {
    }

    FilesystemError::FilesystemError(int errcode,
                                     const std::filesystem::path &path1,
                                     const std::string &what)
        : FilesystemError(errcode, path1, {}, what)
    {
    }

    FilesystemError::FilesystemError(int errcode,
                                     const std::filesystem::path &path1)
        : FilesystemError(errcode, path1, {}, strerror(errcode))
    {
    }

    //==========================================================================
    // DeviceError

    DeviceError::DeviceError(const std::string &text,
                             const std::string &device,
                             Code code,
                             const std::string &id,
                             status::Level level,
                             status::Flow flow,
                             const dt::TimePoint &dt,
                             const types::KeyValueMap &attributes)
        : Super({text,                        // text
                 status::Domain::PERIPHERAL,  // domain
                 device,                      // origin
                 code,                        // code
                 id,                          // id
                 level,                       // level
                 flow,                        // flow
                 dt,                          // timepoint
                 attributes},                 // attributes
                std::runtime_error(text))
    {
    }

    //==========================================================================
    // Error mapping methods

    status::Event::Ref map_to_event(const std::exception &e) noexcept
    {
        if (auto *ep = dynamic_cast<const status::Event *>(&e))
        {
            return std::make_shared<status::Event>(*ep);
        }
        else if (auto *ep = dynamic_cast<const fs::filesystem_error *>(&e))
        {
            return std::make_shared<FilesystemError>(*ep);
        }
        else if (auto *ep = dynamic_cast<const std::system_error *>(&e))
        {
            return std::make_shared<SystemError>(*ep);
        }
        else if (auto *ep = dynamic_cast<const std::invalid_argument *>(&e))
        {
            return std::make_shared<InvalidArgument>(ep->what());
        }
        else if (auto *ep = dynamic_cast<const std::length_error *>(&e))
        {
            return std::make_shared<InvalidLength>(ep->what());
        }
        else if (auto *ep = dynamic_cast<const std::logic_error *>(&e))
        {
            return std::make_shared<FailedPrecondition>(ep->what());
        }
        else if (auto *ep = dynamic_cast<const std::out_of_range *>(&e))
        {
            return std::make_shared<OutOfRange>(ep->what());
        }
        else if (auto *ep = dynamic_cast<const std::runtime_error *>(&e))
        {
            return std::make_shared<RuntimeError>(ep->what());
        }
        else
        {
            return std::make_shared<RuntimeError>(e.what());
        }
    }

    status::Event::Ref map_to_event(std::exception_ptr eptr) noexcept
    {
        if (eptr)
        {
            try
            {
                std::rethrow_exception(eptr);
            }
            catch (const std::exception &e)
            {
                return map_to_event(e);
            }
            catch (...)
            {
                return std::make_shared<status::Event>(
                    "Non-standard error",         // text
                    status::Domain::APPLICATION,  // domain
                    platform::path->exec_name(),  // origin
                    0,                            // code
                    "UNKNOWN",                    // symbol
                    status::Level::FAILED,        // level
                    status::Flow::ABORTED);       // flow
            }
        }
        else
        {
            return {};
        }
    }
}  // namespace picarro::exception

namespace std
{
    /// Define output stream operator "<<" on std::exception and derivatives.
    std::ostream &operator<<(std::ostream &stream, const exception &e)
    {
        picarro::exception::map_to_event(e)->to_stream(stream);
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, exception_ptr eptr)
    {
        if (auto ep = picarro::exception::map_to_event(eptr))
        {
            ep->to_stream(stream);
        }
        return stream;
    }
}  // namespace std
