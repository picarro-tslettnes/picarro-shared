/// -*- c++ -*-
//==============================================================================
/// @file zmq-messagehandler.c++
/// @brief Process received message publications
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "zmq-messagehandler.h++"

namespace picarro::zmq
{
    MessageHandler::MessageHandler(const std::string &id, const Filter &filter)
        : id_(id),
          filter_(filter)
    {
    }

    const std::string &MessageHandler::id() const noexcept
    {
        return this->id_;
    }

    const Filter &MessageHandler::filter() const noexcept
    {
        return this->filter_;
    }
}  // namespace picarro::zmq
