/// -*- c++ -*-
//==============================================================================
/// @file translate-idl-eventtypes.c++
/// @brief Encode/decode routines for common IDL error/status types
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "translate-idl-eventtypes.h++"
#include "translate-idl-inline.h++"
#include "chrono/date-time.h++"

namespace picarro::idl
{
    //==========================================================================
    // Domain
    void encode(const picarro::status::Domain &native, Picarro::Status::Domain *idl) noexcept
    {
        *idl = static_cast<Picarro::Status::Domain>(native);
    }

    void decode(const Picarro::Status::Domain &idl, picarro::status::Domain *native) noexcept
    {
        *native = static_cast<picarro::status::Domain>(idl);
    }

    //==========================================================================
    // Severity
    void encode(const picarro::status::Level &native, Picarro::Status::Level *idl) noexcept
    {
        *idl = static_cast<Picarro::Status::Level>(native);
    }

    void decode(const Picarro::Status::Level &idl, picarro::status::Level *native) noexcept
    {
        *native = static_cast<picarro::status::Level>(idl);
    }

    //==========================================================================
    // Event
    void encode(const picarro::status::Event &native, Picarro::Status::Event *idl) noexcept
    {
        idl->text(native.text());
        encode(native.domain(), &idl->domain());
        idl->origin(native.origin());
        encode(native.level(), &idl->level());
        encode(native.timepoint(), &idl->timestamp());
        encode(native.attributes(), &idl->attributes());
    }

    void decode(const Picarro::Status::Event &idl, picarro::status::Event *native) noexcept
    {
        *native = decoded_event(idl);
    }

    picarro::status::Event decoded_event(const Picarro::Status::Event &idl) noexcept
    {
        return {
            idl.text(),                                        // text
            decoded<picarro::status::Domain>(idl.domain()),         // domain
            idl.origin(),                                      // origin
            decoded<picarro::status::Level>(idl.level()),           // level
            decoded<picarro::dt::TimePoint>(idl.timestamp()),       // timepoint
            decoded<picarro::types::KeyValueMap>(idl.attributes())  // attributes
        };
    }

    //==========================================================================
    // LogMessage

    void encode(const picarro::logging::Message &native,
                Picarro::Status::LogMessage *idl) noexcept
    {
        idl->text(native.text());
        idl->domain(Picarro::Status::Domain::APPLICATION);
        idl->origin(native.origin());
        encode(native.level(), &idl->level());
        encode(native.timepoint(), &idl->timestamp());
        encode(native.attributes(), &idl->attributes());
        idl->log_scope(native.scopename());
        idl->filename(native.path().string());
        idl->lineno(native.lineno());
        idl->function(native.function());
        idl->thread_id(native.thread_id());
    }

    picarro::logging::Message decoded_logmessage(Picarro::Status::LogMessage idl) noexcept
    {
        return {
            picarro::logging::scopes.get(idl.log_scope()),
            decoded<picarro::status::Level>(idl.level()),
            decoded<picarro::dt::TimePoint>(idl.timestamp()),
            idl.filename(),
            idl.lineno(),
            idl.function(),
            static_cast<pid_t>(idl.thread_id()),
            idl.origin(),
            decoded<picarro::types::KeyValueMap>(idl.attributes()),
            idl.text(),
        };
    }

    //==========================================================================
    // ErrorEvent
    void encode(const picarro::status::Error &native, Picarro::Status::ErrorEvent *idl) noexcept
    {
        encode(static_cast<picarro::status::Event>(native), static_cast<Picarro::Status::Event *>(idl));
        idl->code(native.code());
        idl->symbol(native.symbol());
    }

    void decode(const Picarro::Status::ErrorEvent &idl, picarro::status::Error *native) noexcept
    {
        *native = decoded_error(idl);
    }

    picarro::status::Error decoded_error(const Picarro::Status::ErrorEvent &idl) noexcept
    {
        return {
            idl.text(),                                        // text
            decoded<picarro::status::Domain>(idl.domain()),         // domain
            idl.origin(),                                      // origin
            static_cast<int>(idl.code()),                      // code
            idl.symbol(),                                      // symbol
            decoded<picarro::status::Level>(idl.level()),           // level
            decoded<picarro::dt::TimePoint>(idl.timestamp()),       // timepoint
            decoded<picarro::types::KeyValueMap>(idl.attributes())  // attributes
        };
    }

}  // namespace picarro::idl
