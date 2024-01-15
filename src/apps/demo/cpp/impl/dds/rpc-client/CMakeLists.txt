## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build DDS RPC client library for demo application
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream
### libraries/executables.
set(TARGET picarro_demo_dds_client)

### What kind of library we are building (STATIC|SHARED|OBJECT|...); the default
### is STATIC. See: https://cmake.org/cmake/help/latest/command/add_library.html.
set(LIB_TYPE STATIC)

### Static/shared library dependencies, either from this build or provided by the system.
set(LIB_DEPS
  picarro_demo_api
  picarro_demo_dds_types
  picarro_demo_dds_subscriber
  picarro_shared_ipc_dds_rti
)

### Source files
set(SOURCES
  demo-dds-client.c++
  )

### Invoke common CMake rules
include(BuildLibrary)
