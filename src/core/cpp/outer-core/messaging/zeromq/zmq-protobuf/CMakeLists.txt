## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_core_messaging_zmq_protobuf)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_zmq_base
  picarro_core_io_protobuf
)

### Source files in this folder
set(SOURCES
  zmq-protobuf-error.c++
  zmq-protobuf-client.c++
  zmq-protobuf-requesthandler.c++
  zmq-protobuf-server.c++
)

### Recepies to build the library
include(BuildLibrary)
