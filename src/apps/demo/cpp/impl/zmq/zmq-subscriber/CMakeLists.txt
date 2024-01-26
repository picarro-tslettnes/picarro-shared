## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description Picarro Demo Application - ZeroMQ Subscriber module
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream
### libraries/executables.
set(TARGET picarro_demo_zmq_subscriber)

### What kind of library we are building (STATIC|SHARED|OBJECT|...); the default
### is STATIC.  See:
### https://cmake.org/cmake/help/latest/command/add_library.html.
set(LIB_TYPE STATIC)

### Static/shared library dependencies, either from this build or provided by the system.
set(LIB_DEPS
  picarro_demo_zmq_common
)

### Source files
set(SOURCES
  demo-zmq-subscriber.c++
)

### Invoke common CMake rules
include(BuildLibrary)
