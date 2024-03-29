## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build platform-specific code - POSIX version
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_platform_posix)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies
set(LIB_DEPS
  picarro_core_common
)

### Sources
set(SOURCES
  posix-providers.c++
  posix-symbols.c++
  posix-path.c++
  posix-process.c++
  posix-runtime.c++
  posix-timezone.c++
  posix-logsink.c++
)

### Build library
include(BuildLibrary)
