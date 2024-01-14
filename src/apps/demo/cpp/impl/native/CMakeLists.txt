## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description Build native implementation of Picarro Demo
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_demo_native)

### Make this an OBJECT library whose files will be included direcly in dowstream dependants
set(LIB_TYPE STATIC)

### Static/shared library dependencies.
set(LIB_DEPS
  picarro_demo_api)

set(SOURCES
  demo-native.c++)

## Invoke common CMake rules
include(BuildLibrary)
