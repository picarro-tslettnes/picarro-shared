// -*- c++ -*-
//==============================================================================
/// @file grpc-status.c++
/// @brief gRPC status with detailed error data
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "grpc-status.h++"
#include "translate-protobuf-event.h++"
#include "translate-protobuf-variant.h++"
#include "translate-protobuf-google.h++"
#include "translate-protobuf-inline.h++"
#include "platform/symbols.h++"
#include "status/error.h++"
#include "status/exceptions.h++"

#include "grpc-status-names.gen"  // Generated by `create_grpcstatus.py`

namespace picarro::grpc
{

    //==========================================================================
    // \class Status

    Status::Status()
    {
    }

    Status::Status(const ::grpc::Status &status)
        : ::grpc::Status(status.error_code(),
                         status.error_message(),
                         status.error_details())
    {
        protobuf::decode(this->details(), static_cast<status::Error *>(this));
    }

    Status::Status(const Status &status)
        : Status(status.status_code(), status)
    {
    }

    Status::Status(const Error &error)
        : Status(Status::code_from_error(error), error)
    {
    }

    Status::Status(const Picarro::Status::Details &details)
        : status::Error(
              details.text(),
              protobuf::decoded<status::Domain>(details.domain()),
              details.origin(),
              details.code(),
              details.symbol(),
              protobuf::decoded<status::Level>(details.level()),
              protobuf::decoded<dt::TimePoint>(details.timestamp()),
              protobuf::decoded<types::KeyValueMap>(details.attributes())),
          ::grpc::Status(
              Status::code_from_error(*this),
              details.text(),
              details.SerializeAsString())
    {
    }

    Status::Status(::grpc::StatusCode status_code,
                   const std::string &text,
                   const Picarro::Status::Details &details)
        : Error(
              text,
              protobuf::decoded<status::Domain>(details.domain()),
              details.origin(),
              details.code(),
              details.symbol(),
              protobuf::decoded<status::Level>(details.level()),
              protobuf::decoded<dt::TimePoint>(details.timestamp()),
              protobuf::decoded<types::KeyValueMap>(details.attributes())),
          ::grpc::Status(
              status_code,
              text,
              details.SerializeAsString())
    {
    }

    Status::Status(::grpc::StatusCode status_code,
                   const Error &error)
        : Status(status_code,
                 error.text(),
                 error.domain(),
                 error.origin(),
                 error.level(),
                 error.timepoint(),
                 error.attributes())
    {
    }

    Status::Status(::grpc::StatusCode status_code,
                   const std::string &text,
                   status::Domain domain,
                   const std::string &origin,
                   status::Level level,
                   const dt::TimePoint &timepoint,
                   const types::KeyValueMap &attributes)
        : Error(text, domain, origin, level, timepoint, attributes),
          ::grpc::Status(
              status_code,
              text,
              protobuf::encoded<Picarro::Status::Details>(
                  *static_cast<Error *>(this))
                  .SerializeAsString())
    {
    }

    ::grpc::StatusCode Status::status_code() const noexcept
    {
        return this->error_code();
    }

    std::string Status::status_code_name() const noexcept
    {
        return Status::status_code_name(this->status_code());
    }

    std::string Status::status_code_name(::grpc::StatusCode status_code) noexcept
    {
        try
        {
            return grpc_status_names.at(status_code);
        }
        catch (const std::out_of_range &e)
        {
            return std::to_string(status_code);
        }
    }

    std::string Status::text() const noexcept
    {
        return this->error_message();
    }

    Picarro::Status::Details Status::details() const noexcept
    {
        Picarro::Status::Details msg;
        msg.ParseFromString(this->error_details());
        return msg;
    };

    void Status::to_stream(std::ostream &stream) const
    {
        types::TaggedValueList fields;
        this->populate_fields(&fields);

        stream << this->class_name()
               << "("
               << this->status_code_name();

        if (!this->text().empty())
        {
            stream << ", " << std::quoted(this->text());
        }

        if (!fields.empty())
        {
            fields.to_stream(stream,  // stream
                             ", ",    // prefix
                             ", ",    // infix
                             "");     // postfix
        }

        stream << ")";
    }

    std::string Status::class_name() const noexcept
    {
        return TYPE_NAME_BASE(Status);
    }

    ::grpc::StatusCode Status::code_from_error(const status::Error &error) noexcept
    {
        switch (error.domain())
        {
        case status::Domain::NONE:
            return error.empty()
                       ? ::grpc::StatusCode::OK
                       : ::grpc::StatusCode::UNKNOWN;

        case status::Domain::APPLICATION:
            return static_cast<::grpc::StatusCode>(error.code());

        case status::Domain::SYSTEM:
            return Status::code_from_errno(error.code());

        case status::Domain::PERIPHERAL:
            return grpc::StatusCode::ABORTED;

        default:
            return grpc::StatusCode::UNKNOWN;
        }
    }

    ::grpc::StatusCode Status::code_from_errno(int err) noexcept
    {
        switch (static_cast<std::errc>(err))
        {
        case std::errc::operation_canceled:
            return ::grpc::StatusCode::CANCELLED;

        case std::errc::address_in_use:
        case std::errc::file_exists:
            return ::grpc::StatusCode::ALREADY_EXISTS;

        case std::errc::no_such_file_or_directory:
        case std::errc::no_such_device_or_address:
        case std::errc::no_such_device:
        case std::errc::no_such_process:
            return ::grpc::StatusCode::NOT_FOUND;

        case std::errc::permission_denied:
        case std::errc::operation_not_permitted:
            return ::grpc::StatusCode::PERMISSION_DENIED;

        case std::errc::argument_out_of_domain:
        case std::errc::result_out_of_range:
            return ::grpc::StatusCode::OUT_OF_RANGE;

        case std::errc::file_too_large:
        case std::errc::no_space_on_device:
            return ::grpc::StatusCode::RESOURCE_EXHAUSTED;

        case std::errc::filename_too_long:
            return ::grpc::StatusCode::INVALID_ARGUMENT;

        case std::errc::device_or_resource_busy:
        case std::errc::resource_unavailable_try_again:
        case std::errc::operation_in_progress:
        case std::errc::text_file_busy:
            return ::grpc::StatusCode::ABORTED;

        default:
            return ::grpc::StatusCode::FAILED_PRECONDITION;
        }
    }

    void Status::throw_if_error() const
    {
        if (!this->ok())
        {
            if (std::exception_ptr eptr = this->as_exception_ptr())
            {
                std::rethrow_exception(eptr);
            }
        }
    }

    std::exception_ptr Status::as_exception_ptr() const
    {
        std::exception_ptr eptr = {};
        switch (this->domain())
        {
        case status::Domain::NONE:
            if (!this->ok())
            {
                return this->as_application_error();
            }
            else
            {
                return {};
            }

        case status::Domain::PERIPHERAL:
            return this->as_device_error();

        case status::Domain::SYSTEM:
            return this->as_system_error();

        case status::Domain::APPLICATION:
            return this->as_application_error();

        default:
            return {};
        }
    }

    std::exception_ptr Status::as_device_error() const
    {
        return std::make_exception_ptr<exception::DeviceError>(
            {this->text(),
             this->origin(),
             this->code(),
             this->symbol(),
             this->level(),
             this->timepoint(),
             this->attributes()});
    }

    std::exception_ptr Status::as_system_error() const
    {
        types::Value path1 = this->attribute("path1");
        types::Value path2 = this->attribute("path2");
        if (path1 || path2)
        {
            return std::make_exception_ptr<exception::FilesystemError>(*this);
        }
        else
        {
            return std::make_exception_ptr<exception::SystemError>(*this);
        }
    }

    std::exception_ptr Status::as_application_error() const
    {
        switch (this->status_code())
        {
        case ::grpc::StatusCode::CANCELLED:
            return std::make_exception_ptr<exception::Cancelled>(*this);

        case ::grpc::StatusCode::DEADLINE_EXCEEDED:
            return std::make_exception_ptr<exception::Timeout>(*this);

        case ::grpc::StatusCode::INVALID_ARGUMENT:
            return std::make_exception_ptr<exception::InvalidArgument>(*this);

        case ::grpc::StatusCode::OUT_OF_RANGE:
            return std::make_exception_ptr<exception::OutOfRange>(*this);

        case ::grpc::StatusCode::FAILED_PRECONDITION:
            return std::make_exception_ptr<exception::FailedPrecondition>(*this);

        case ::grpc::StatusCode::NOT_FOUND:
            return std::make_exception_ptr<exception::NotFound>(*this);

        case ::grpc::StatusCode::ALREADY_EXISTS:
            return std::make_exception_ptr<exception::Duplicate>(*this);

        case ::grpc::StatusCode::PERMISSION_DENIED:
            return std::make_exception_ptr<exception::PermissionDenied>(*this);

        case ::grpc::StatusCode::RESOURCE_EXHAUSTED:
            return std::make_exception_ptr<exception::ResourceExhausted>(*this);

        case ::grpc::StatusCode::ABORTED:
            return std::make_exception_ptr<exception::RuntimeError>(*this);

        case ::grpc::StatusCode::UNAVAILABLE:
            return std::make_exception_ptr<exception::Unavailable>(*this);

        default:
            return std::make_exception_ptr<exception::UnknownError>(*this);
        }
    }

}  // namespace picarro::grpc