## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_common)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Upstream package dependencies
if(BUILD_RAPIDJSON)
  set(PKG_DEPS RapidJSON)
endif()

## Include appropriate system libraries based on platform
if(PLATFORM_QNX)
  list(APPEND LIB_DEPS c++fs)
elseif(LINUX)
  list(APPEND LIB_DEPS stdc++fs)
elseif(WIN32)
  list(APPEND LIB_DEPS dbghelp)
endif()

## Invoke common CMake rules
include(BuildLibrary)

### C++17 required for variant data type, parameter packs, std::filesystem
target_compile_features(${TARGET} PUBLIC cxx_std_17)

# Pull in sources from subdirectories
add_subdirectory(argparse)
add_subdirectory(buildinfo)
add_subdirectory(chrono)
add_subdirectory(io)
add_subdirectory(json)
add_subdirectory(logging)
add_subdirectory(platform)
add_subdirectory(settings)
add_subdirectory(status)
add_subdirectory(string)
add_subdirectory(thread)
add_subdirectory(types)

