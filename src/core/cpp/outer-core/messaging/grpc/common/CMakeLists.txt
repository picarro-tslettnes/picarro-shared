## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream libraries/executables.
set(TARGET picarro_core_messaging_grpc_common)

### Third party package dependency
find_package(grpc REQUIRED)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_core_messaging_common
  picarro_core_io_protobuf
  gRPC::grpc++
)

set(SOURCES
  grpc-base.c++
  grpc-status.c++
)


### Recepies to build the library
include(BuildLibrary)

### Include binary output dir
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

### Generate "grpc-status-names.gen"
set(GRPCSTATUSFILE   ${CMAKE_CURRENT_BINARY_DIR}/grpc-status-names.gen)
set(GRPCSTATUSSCRIPT ${BUILD_SCRIPTS_DIR}/generate_grpcstatus.py)
add_custom_command(
    OUTPUT ${GRPCSTATUSFILE}
    COMMAND python3 ${GRPCSTATUSSCRIPT} --output ${GRPCSTATUSFILE} --sysroot "${BUILD_ROOT}/"
    COMMENT "Generating ${GRPCSTATUSFILE}"
    BYPRODUCTS ${GRPCSTATUSFILE})
add_custom_target(grpcstatuslist DEPENDS ${GRPCSTATUSFILE})
add_dependencies(${TARGET} grpcstatuslist)

### Define preprocessor symbol
target_compile_definitions(${TARGET} PUBLIC USE_GRPC=1)
