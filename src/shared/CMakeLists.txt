##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

if(USE_CPP)
  add_subdirectory(cpp)
endif()

if(USE_PYTHON)
  add_subdirectory(python)
endif()

if(USE_RTI_DDS)
  add_subdirectory(idl)
endif()

if(USE_GRPC)
  add_subdirectory(proto)
endif()

### Create interface library to encapsulate the above
set(TARGET picarro_shared)
set(LIB_TYPE INTERFACE)
set(LIB_DEPS
  picarro_shared_core
  picarro_shared_platform
  picarro_shared_ipc_api
  picarro_shared_idl
  picarro_shared_protodefs
  )

include(BuildLibrary)

### Install "settings/" folder as data
install(DIRECTORY settings TYPE DATA)
