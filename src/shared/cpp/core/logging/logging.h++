/// -*- c++ -*-
//==============================================================================
/// @file logging.h++
/// @brief Logging interface
/// @author Tor Slettnes <tslettnes@picarro.com>
///
/// Logging framework, mainly comprising these classes
///  * `Message()`, representing a log entry
///  * `MessageBuilder()`, derived from `Message()` to construct a log entry
///     from `std::ostream` compatible elements (i.e. objects that support the
///     `<<` operator), optionally with an initial format string.
///  * `LogSink()`, an abstract backend for backends that send the message
///    to specific destination (log file, json file, syslog, etc).
///  * `LogDispatcher()` to distribute a message to applicable sinks.
///  * Wrapper macros \b log_message(), \b log_trace(), \b log_debug(), ...,
/// @b log_error(), to create, build, and dispatch the message in one call.
///
///  * Wrapper macros \b logf_message(), \b logf_trace(), \b logf_debug(), ...,
/// @b logf_error(), to construct and log in place a message from a format
///
///    template followed by corresponding arguments.
/// @b Usage
///
///  * Instantiate one or more backends ("sinks").  This is normally done by
///    indirectly by instantiating
///    [argparse::ClientOptions](../argparse/client.h++) or
///    [argparse::ServerOptions](../argparse/server.h++), which in turn creates
///    desired sinks based on selected command line options.
///  * To log a message in a single call, invoke one of
///    \code
///      log_message(status::Level::LEVELNAME, arg, ...);
///      log_trace(arg, ...);
///      log_debug(arg, ...);
///      log_info(arg, ...);
///      log_notice(arg, ...);
///      log_warning(arg, ...);
///      log_error(arg, ...);
///      log_critical(arg, ...);
///      log_fatal(arg, ...);
///    \endcode
///    Or, using a format template:
///    \code
///      logf_message(status::Level::LEVELNAME, format, ...);
///      logf_trace(format, ...);
///      logf_debug(format, ...);
///      logf_info(format, ...);
///      logf_notice(format, ...);
///      logf_warning(format, ...);
///      logf_error(format, ...);
///      logf_critical(format, ...);
///      logf_fatal(format, ...);
///    \endcode
///  * Alternatively, to build a message in steps:
///    \code
///      picarro::Logging::MessageBuilder::Ref msg = create_log_message(status::Level::LEVELNAME);
///      *msg << arg << ... ;
///      ...
///      msg->submit();
///    \endcode
/// \note
///     For performance reasons, the output string is not actually generated
///     unless there exists at least one sink with \a threshold >= \a LEVELNAME.
///     For this reason, it is preferable to pass raw components on the message
///     as they are, so long as they do or can be made to support C++ output
///     streams. For an example, see the mix-in class
///     [types::Streamable](../types/streamable.h++).
//==============================================================================

#pragma once
#include "message/builder.h++"
#include "dispatcher.h++"

//==============================================================================
/// Wrapper macros for generating & logging a message in one step.  Macros are
/// used rather than function templates in order to preserve source context for
/// Message() constructor, below.
///
/// Construct messages by sending each provided argument directly to the output
/// stream, with no additional formatting. Arguments must be supported by the
/// "<<" output stream operator. Frequently, this means the appropriate header
/// file needs to be included.

#define custom_log_message(level, timepoint, path, lineno, function) \
    picarro::logging::MessageBuilder::create_shared(                      \
        &picarro::logging::message_dispatcher,                            \
        log_scope,                                                   \
        level,                                                       \
        timepoint,                                                   \
        path,                                                        \
        lineno,                                                      \
        function)

#define default_log_message(level) \
    custom_log_message(            \
        level,                     \
        picarro::dt::Clock::now(),      \
        __builtin_FILE(),          \
        __builtin_LINE(),          \
        __builtin_FUNCTION())

#define log_message(level, ...) default_log_message(level)->add(__VA_ARGS__).dispatch()
#define log_trace(...)          log_message(picarro::status::Level::TRACE, __VA_ARGS__)
#define log_debug(...)          log_message(picarro::status::Level::DEBUG, __VA_ARGS__)
#define log_info(...)           log_message(picarro::status::Level::INFO, __VA_ARGS__)
#define log_notice(...)         log_message(picarro::status::Level::NOTICE, __VA_ARGS__)
#define log_warning(...)        log_message(picarro::status::Level::WARNING, __VA_ARGS__)
#define log_error(...)          log_message(picarro::status::Level::FAILED, __VA_ARGS__)
#define log_critical(...)       log_message(picarro::status::Level::CRITICAL, __VA_ARGS__)
#define log_fatal(...)          log_message(picarro::status::Level::FATAL, __VA_ARGS__)

/// Construct messages from an format template and corresponding arguments.
/// Arguments must be supported by the "<<" output stream operator.  See
/// [string/format.h++](../string/format.h++) for details.

#define logf_message(level, ...) default_log_message(level)->format(__VA_ARGS__).dispatch()
#define logf_trace(...)          logf_message(picarro::status::Level::TRACE, __VA_ARGS__)
#define logf_debug(...)          logf_message(picarro::status::Level::DEBUG, __VA_ARGS__)
#define logf_info(...)           logf_message(picarro::status::Level::INFO, __VA_ARGS__)
#define logf_notice(...)         logf_message(picarro::status::Level::NOTICE, __VA_ARGS__)
#define logf_warning(...)        logf_message(picarro::status::Level::WARNING, __VA_ARGS__)
#define logf_error(...)          logf_message(picarro::status::Level::FAILED, __VA_ARGS__)
#define logf_critical(...)       logf_message(picarro::status::Level::CRITICAL, __VA_ARGS__)
#define logf_fatal(...)          logf_message(picarro::status::Level::FATAL, __VA_ARGS__)

#ifndef NDEBUG
/// Evaluate a condition, exit with a fatal error if it fails.
#define assertf(cond, ...)                                                           \
    if (!(cond))                                                                     \
    {                                                                                \
        logf_message(picarro::status::Level::FATAL, "Assertion failed: "s + __VA_ARGS__); \
        throw std::terminate;                                                        \
    }
#else
#define assertf(cond, ...)
#endif

namespace picarro::logging
{
    extern Dispatcher message_dispatcher;
}
