## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build protocol buffer bindings
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### This can be used as a downstream dependency.
set(TARGET picarro_core_proto)

### What type of library are we building?
set(LIB_TYPE STATIC)

### Source files
set(SOURCES
  variant_types.proto
  event_types.proto
  signal_types.proto
  request_reply.proto
)

### Invoke common CMake rules
include(BuildProtodefs)
