## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build platform-specific code - QNX version
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_platform_qnx)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies
set(LIB_DEPS
  picarro_core_platform_posix
)

### Sources
set(SOURCES
  qnx-providers.c++
  qnx-path.c++
)

### Build library
include(BuildLibrary)
