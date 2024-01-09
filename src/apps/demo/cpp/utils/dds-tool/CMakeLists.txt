##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build DDS Demo tool
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this executable. This also becomes the name of the project.
set(TARGET demo-dds-tool)

### Libraries we depend on, either from this build or provided by the
### system.
set(LIB_DEPS
#  picarro_demo_dds_requesters
  picarro_demo_dds_client
  picarro_demo_native
  picarro_demo_tool_common
)

### Source files
set(SOURCES
  main.c++
  )

## Invoke common CMake rules to build executable
include(BuildExecutable)
