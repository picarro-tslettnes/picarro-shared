##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro Demo - client utilities
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(common)

if(USE_RTI_DDS)
  add_subdirectory(dds-tool)
endif()

if(USE_GRPC)
  add_subdirectory(grpc-tool)
endif()

