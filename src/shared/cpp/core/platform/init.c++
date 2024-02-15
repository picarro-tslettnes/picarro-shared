/// -*- c++ -*-
//==============================================================================
/// @file init.h++
/// @brief Application startup/shutdown
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "init.h++"
#include "logging/logging.h++"

namespace shared::platform
{
    //==========================================================================
    // Task

    Task::Task(const std::string &handle, const Function &functor)
        : Function(functor),
          handle(handle)
    {
    }


    //==========================================================================
    // InitTask

    InitTask::InitTask(const std::string &handle, const Function &functor)
        : Task(handle, functor)
    {
        init_tasks.insert(this);
        // signal_startup.connect(handle, *this);
    }

    InitTask::~InitTask()
    {
        init_tasks.erase(this);
        // signal_startup.disconnect(handle);
    }

    //==========================================================================
    // ExitTask

    ExitTask::ExitTask(const std::string &handle, const Function &functor)
        : Task(handle, functor)
    {
        exit_tasks.insert(this);
        // signal_shutdown.connect(handle, *this);
    }

    ExitTask::~ExitTask()
    {
        exit_tasks.erase(this);
        // signal_shutdown.disconnect(handle);
    }

    //==========================================================================
    // TaskSet

    void TaskSet::execute() const
    {
        for (const Task* task : *this)
        {
            (*task)();
        }
    }

    //==========================================================================
    // Global symbols

    // TaskSet init_tasks;
    // TaskSet exit_tasks;

    shared::signal::VoidSignal signal_startup("signal_startup");
    shared::signal::VoidSignal signal_shutdown("signal_shutdown");
}  // namespace shared::platform