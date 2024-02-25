## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build protocol buffer bindings
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### This can be used as a downstream dependency.
set(TARGET picarro_demo_protodefs)

### What type of library are we building?
set(LIB_TYPE STATIC)

### Static/shared library dependencies.
set(PROTO_DEPS picarro_core_proto)

### Source files
set(SOURCES
  demo_types.proto
  demo_service.proto
)

### Invoke common CMake rules
include(BuildProtodefs)
