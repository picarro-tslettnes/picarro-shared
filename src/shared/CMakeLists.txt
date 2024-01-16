## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

if(BUILD_CPP)
  add_subdirectory(cpp)
endif()

if(BUILD_PYTHON)
  add_subdirectory(python)
endif()

if(BUILD_PROTOBUF)
  add_subdirectory(proto)
endif()

### Create interface library to encapsulate the above
set(TARGET picarro_shared)
set(LIB_TYPE INTERFACE)
set(LIB_DEPS
  picarro_shared_core
  picarro_shared_platform
)

if(BUILD_PROTOBUF)
  list(APPEND LIB_DEPS
    picarro_shared_protodefs
    picarro_shared_ipc_protobuf
  )
endif()

if(BUILD_GRPC)
  list(APPEND LIB_DEPS
    picarro_shared_ipc_grpc
  )
endif()


include(BuildLibrary)

### Install "settings/" folder as data
install(DIRECTORY settings TYPE DATA)
