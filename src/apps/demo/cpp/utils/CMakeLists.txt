## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro Demo - client utilities
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(common)

if(BUILD_RTI_DDS)
  add_subdirectory(dds-tool)
endif()

if(BUILD_GRPC)
  add_subdirectory(grpc-tool)
endif()

if(BUILD_ZMQ)
  add_subdirectory(zmq-tool)
endif()

