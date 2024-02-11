## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build service API library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_shared_ipc_common)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_core)

### Source files, roughly in dependency order
set(SOURCES
  ipc-endpoint.c++
)

## Invoke common CMake rules
include(BuildLibrary)
