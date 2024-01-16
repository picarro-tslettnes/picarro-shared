## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief CMake build recipe for Common Core components
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

cmake_minimum_required(VERSION 3.15)

if (NOT PROJECT_NAME)
  project(common_core
    VERSION 0.0.1)
endif()


include(${CMAKE_CURRENT_LIST_DIR}/cmake/BuildProject.cmake)

### C++ Components
option(BUILD_CPP        "Build/Install C++ code" ON)

### Python Components
option(BUILD_PYTHON     "Install Python clients/scripts" ON)
set(PYTHON_INSTALL_DIR "share/python")

### gRPC + ProtoBuf
option(BUILD_GRPC       "Build support for gRPC Remote Procedure Calls" ON)
option(BUILD_PROTOBUF   "Build support for Google Protocol Buffers" ON)

### Pull in CMake files to build the actual sources
add_subdirectory(src)
