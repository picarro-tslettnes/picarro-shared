## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description Picarro Demo Application - ZeroMQ client module
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream
### libraries/executables.
set(TARGET picarro_demo_zmq_common)

### What kind of library we are building (STATIC|SHARED|OBJECT|...); the default
### is STATIC.  See:
### https://cmake.org/cmake/help/latest/command/add_library.html.
set(LIB_TYPE INTERFACE)

### Static/shared library dependencies, either from this build or provided by the system.
set(LIB_DEPS
  picarro_demo_api
  picarro_demo_protobuf_types
  picarro_core_messaging_zmq
  picarro_core_io_protobuf
)

set(SOURCES)

### Invoke common CMake rules
include(BuildLibrary)
