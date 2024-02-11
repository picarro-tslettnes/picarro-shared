## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build shared ZeroMQ wrappers
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_shared_ipc_zmq_base)

### Library dependencies.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_ipc_common
  picarro_shared_platform
)

### Package dependencies
set(PKG_DEPS
  libzmq
)

### Source files in this folder
set(SOURCES
  zmq-endpoint.c++
  zmq-host.c++
  zmq-satellite.c++
  zmq-filter.c++
  zmq-publisher.c++
  zmq-subscriber.c++
  zmq-messagehandler.c++
  zmq-messagewriter.c++
  zmq-requester.c++
  zmq-responder.c++
)

### Recepies to build the library
include(BuildLibrary)

### Define preprocessor symbol
target_compile_definitions(${TARGET} PUBLIC USE_ZMQ=1)
