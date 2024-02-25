## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(common)
add_subdirectory(platforms)

set(TARGET picarro_core_inner)
set(LIB_TYPE INTERFACE)
set(LIB_DEPS
  picarro_core_common
  picarro_core_platform
)

include(BuildLibrary)
