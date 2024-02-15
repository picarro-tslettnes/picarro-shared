## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_shared_messaging_http)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_messaging_common
)

### Third-party package dependencies
set(PKG_DEPS
  # curlpp
  libcurl
)

### Source files in this folder
set(SOURCES
  http-client.c++
)

### Recepies to build the library
include(BuildLibrary)

