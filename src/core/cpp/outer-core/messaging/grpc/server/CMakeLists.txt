## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_messaging_grpc_server)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Load `grpc` targets to get reflection lib
find_package(grpc REQUIRED)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_grpc_common
  picarro_core_messaging_http
  gRPC::grpc++_reflection
)

set(SOURCES
  grpc-requesthandler.c++
  grpc-serverbuilder.c++
  grpc-serverinterceptors.c++
)


### Recepies to build the library
include(BuildLibrary)
