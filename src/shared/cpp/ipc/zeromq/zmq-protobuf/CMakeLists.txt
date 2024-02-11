## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_shared_ipc_zmq_protobuf)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_ipc_zmq_base
  picarro_shared_ipc_protobuf
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
