## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Demo application - implementations
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(native)

if(BUILD_RTI_DDS)
  add_subdirectory(dds)
endif()

if(BUILD_GRPC)
  add_subdirectory(grpc)
endif()

