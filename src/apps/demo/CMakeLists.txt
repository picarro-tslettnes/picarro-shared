## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro Demo
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

if (BUILD_CPP)
  add_subdirectory(cpp)
endif()

if (BUILD_PYTHON)
  add_subdirectory(python)
endif()

if (BUILD_PROTOBUF)
  add_subdirectory(proto)
endif()

### Install "settings/" folder as data
install(DIRECTORY settings TYPE DATA)
