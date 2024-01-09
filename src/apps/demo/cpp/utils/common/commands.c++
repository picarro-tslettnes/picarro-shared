// -*- c++ -*-
//==============================================================================
/// @file commands.c++
/// @brief Implements demo commmands
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "options.h++"
#include "demo-provider.h++"
#include "string/convert.h++"
#include "chrono/date-time.h++"

namespace picarro::demo
{
    void Options::say_hello()
    {
        std::string text = this->pop_arg("text");
        picarro::types::KeyValueMap data = this->pop_attributes(false);

        picarro::demo::Greeting greeting(
            text,                                         // text
            this->identity,                               // identity
            picarro::str::convert_from(this->implementation),  // implementation
            picarro::dt::Clock::now(),                         // birth
            data);                                        // data

        picarro::demo::provider->say_hello(greeting);
    }

    void Options::get_current_time()
    {
        std::cout << picarro::demo::provider->get_current_time() << std::endl;
    }

    void Options::start_ticking()
    {
        picarro::demo::provider->start_ticking();
    }

    void Options::stop_ticking()
    {
        picarro::demo::provider->stop_ticking();
    }

    void Options::on_time(const picarro::demo::TimeData &timedata)
    {
        picarro::str::format(std::cout,
                        "signal_time(%s)\n",
                        timedata);
    }

    void Options::on_greeting(picarro::signal::MappingChange change,
                              const std::string &identity,
                              const picarro::demo::Greeting &greeting)
    {
        picarro::str::format(std::cout,
                        "signal_greeting(%s, %r, %s)\n",
                        change,
                        identity,
                        greeting);
    }
}  // namespace picarro::demo
