/// -*- c++ -*-
//==============================================================================
/// @file sync-dispatcher.h++
/// @brief Distribute a captured item to available sinks - blocking flavor
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "dispatcher.h++"
#include <mutex>

namespace picarro::logging
{
    class SyncDispatcher : public Dispatcher
    {
        using Super = Dispatcher;

    public:
        void submit(const types::Loggable::Ref &item) override;

    private:
        std::mutex mtx_;
    };

}  // namespace picarro::logging
