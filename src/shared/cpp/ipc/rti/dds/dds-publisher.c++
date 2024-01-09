/// -*- c++ -*-
//==============================================================================
/// @file dds-publisher.c++
/// @brief A publishing entity/producer in a DDS environment
/// @author Tor Slettnes <tslettnes@picarro.com>
//==============================================================================

#include "dds-publisher.h++"
#include "logging/logging.h++"

namespace picarro::dds
{
    DDS_Publisher::DDS_Publisher(
        const std::string &type,
        const std::string &name,
        int domain_id)
        : Super(type, name, domain_id),
          ::dds::pub::Publisher(this->get_participant())
    {
    }
}  // namespace picarro::dds
