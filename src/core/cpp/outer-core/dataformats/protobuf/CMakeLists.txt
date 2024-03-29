## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief Build ProtoBuf encoder/decoder methods for shared types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

set(TARGET picarro_core_io_protobuf)

find_package(Protobuf REQUIRED)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_common
  picarro_core_proto
  protobuf::libprotobuf
)


if(BUILD_GRPC)
  ## Dumb hack to prevent linking error if we're building several intermediate
  ## libraries, some of which depends on gRPC but others that only depend on
  ## ProtoBuf (For example, `picarro_core_messaging_grpc` plus `picarro_demo_zmq_common`, both
  ## of which depend on this `picarro_core_io_protobuf`)

  find_package(grpc REQUIRED)
  list(APPEND LIB_DEPS gRPC::grpc++)

  # list(APPEND PKG_DEPS
  #   grpc++
  # )
endif()



set(SOURCES
  protobuf-standard-types.c++
  protobuf-variant-types.c++
  protobuf-event-types.c++
  protobuf-message.c++
)

### Recepies to build the library
include(BuildLibrary)
