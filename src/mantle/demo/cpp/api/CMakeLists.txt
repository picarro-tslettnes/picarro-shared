## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro Demo - abstract API
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_demo_api)

### Make this an OBJECT library whose files will be included direcly in dowstream dependants
set(LIB_TYPE STATIC)

### Static/shared library dependencies.
set(LIB_DEPS
  picarro_core
)

set(SOURCES
  demo-types.c++
  demo-signals.c++
  demo-api.c++
  demo-provider.c++
)


## Invoke common CMake rules
include(BuildLibrary)
