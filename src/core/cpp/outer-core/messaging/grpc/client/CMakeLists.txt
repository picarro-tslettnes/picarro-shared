## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_messaging_grpc_client)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_grpc_common
  picarro_core_messaging_http
)

set(SOURCES
  grpc-clientbase.c++
)


### Recepies to build the library
include(BuildLibrary)
