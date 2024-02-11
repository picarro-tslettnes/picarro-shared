// -*- c++ -*-
//==============================================================================
/// @file python-pickle.h++
/// @brief Python pickle/unpickle environment
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "python-containerobject.h++"
#include "python-runtime.h++"

namespace picarro::python
{
    class Pickler : public Runtime
    {
    public:
        Pickler();

        ContainerObject unpickle(const types::ByteVector &bytes);
        types::ByteVector pickle(const SimpleObject &object);
    };

    extern Pickler pickler;
};  // namespace picarro::python
