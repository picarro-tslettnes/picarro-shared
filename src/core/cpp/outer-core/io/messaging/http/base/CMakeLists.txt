## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_core_messaging_http)

### We need cURL for this
find_package(CURL
  REQUIRED COMPONENTS HTTP HTTPS)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_common
  CURL::libcurl
)

### Source files in this folder
set(SOURCES
  http-utils.c++
  http-client.c++
)

### Recepies to build the library
include(BuildLibrary)

