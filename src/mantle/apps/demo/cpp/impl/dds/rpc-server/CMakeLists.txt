## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Demo DDS service
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library. This can be used as a dependency for downstream
### libraries/executables.
set(TARGET picarro_demo_dds_service)

### What kind of library we are building (STATIC|SHARED|OBJECT|...); the default
### is STATIC.  See:
### https://cmake.org/cmake/help/latest/command/add_library.html.
set(LIB_TYPE STATIC)

### Static/shared library dependencies, either from this build or provided by the system.
set(LIB_DEPS
  picarro_demo_api
  picarro_demo_dds_types
  picarro_demo_dds_publisher
  picarro_core_messaging_dds_rti
)

### Source files
set(SOURCES
  demo-dds-requesthandler.c++
  demo-dds-service.c++
  demo-dds-run.c++
)


### Invoke common CMake rules
include(BuildLibrary)
