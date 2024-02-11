/// -*- c++ -*-
//==============================================================================
/// @file python-containerobject.h++
/// @brief Data access for Python objects with exposed attributes
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#pragma once
#include "python-simpleobject.h++"

namespace picarro::python
{
    //==========================================================================
    /// @brief
    ///   RAII Wrapper for Python C objects with attribute lookups

    class ContainerObject : public SimpleObject
    {
    public:
        // Inherit constructors
        using SimpleObject::SimpleObject;

        /// @brief
        ///    Obtain attribute names within this container instance.
        /// @return
        ///    Attribute names contained in this instance
        std::vector<std::string> dir() const;
        ContainerObject getattr(const std::string& name) const;

        Map attributes_as_objects() const;
        types::KeyValueMap attributes_as_values() const;
    };
}  // namespace picarro::python