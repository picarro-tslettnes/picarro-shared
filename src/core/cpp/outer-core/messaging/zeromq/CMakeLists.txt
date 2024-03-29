## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

if(BUILD_ZMQ)
  ### Name of this library.
  set(TARGET   picarro_core_messaging_zmq)
  set(LIB_TYPE INTERFACE)

  add_subdirectory(zmq-base)
  set(LIB_DEPS picarro_core_messaging_zmq_base)

  if(BUILD_PROTOBUF)
    add_subdirectory(zmq-protobuf)
    list(APPEND LIB_DEPS picarro_core_messaging_zmq_protobuf)
  endif()

  if(BUILD_PYTHON_IO)
    add_subdirectory(zmq-pypickle)
    list(APPEND LIB_DEPS picarro_core_messaging_zmq_pypickle)
  endif()

  include(BuildLibrary)
endif()
