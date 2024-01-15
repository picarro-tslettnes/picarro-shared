## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief Build ProtoBuf encoder/decoder methods for Demo types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

set(TARGET picarro_demo_protobuf)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_demo_api
  picarro_demo_protodefs
  picarro_shared_ipc_protobuf
)

### External package dependencies, configured via `pkg-config`.
set(PKG_DEPS
  protobuf
)

set(SOURCES
  translate-protobuf-demo.c++
)

### Recepies to build the library
include(BuildLibrary)
