## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_core_messaging_rest)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_http
)

### Source files in this folder
set(SOURCES
  rest-base.c++
  rest-client.c++
)

### Recepies to build the library
include(BuildLibrary)

