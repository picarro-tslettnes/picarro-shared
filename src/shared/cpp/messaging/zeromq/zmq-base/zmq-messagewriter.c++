/// -*- c++ -*-
//==============================================================================
/// @file zmq-protobuf-messagewriter.c++
/// @brief Publish messages with optional topic filter
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "zmq-messagewriter.h++"
#include "status/exceptions.h++"
#include "logging/logging.h++"

namespace shared::zmq
{
    MessageWriter::MessageWriter(const std::shared_ptr<Publisher> &publisher,
                                 const Filter &filter)
        : publisher_(publisher),
          filter_(filter)
    {
        log_trace("Created ZMQ writer with filter: ", filter);
    }

    const Filter &MessageWriter::filter() const noexcept
    {
        return this->filter_;
    }

    std::shared_ptr<Publisher> MessageWriter::publisher() const
    {
        return this->publisher_.lock();
    }

    void MessageWriter::write(const types::ByteVector &bytes)
    {
        if (auto publisher = this->publisher())
        {
            publisher->publish(this->filter_, bytes);
        }
    }

}  // namespace shared::zmq