## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief Build ProtoBuf encoder/decoder methods for shared types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

set(TARGET picarro_shared_messaging_protobuf)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_core
  picarro_shared_protodefs
)

### External package dependencies, configured via `pkg-config`.
set(PKG_DEPS
  protobuf
)

## Dumb hack to prevent linking error if we're building several intermediate
## libraries, some of which depends on gRPC but others that only depend on
## ProtoBuf (For example, `picarro_shared_messaging_grpc` plus `picarro_demo_zmq_common`, both
## of which depend on this `picarro_shared_messaging_protobuf`)

if(BUILD_GRPC)
  list(APPEND PKG_DEPS
    grpc++
  )
endif()

set(SOURCES
  protobuf-standard-types.c++
  protobuf-variant-types.c++
  protobuf-event-types.c++
  protobuf-message.c++
)

### Recepies to build the library
include(BuildLibrary)
