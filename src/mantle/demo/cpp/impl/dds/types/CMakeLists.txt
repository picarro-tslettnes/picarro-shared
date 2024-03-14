## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief Build IDL encoder/decoder methods for demo types conversions
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

set(TARGET picarro_demo_dds_types)

### Library type.  We use static linking for convenience.
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_demo_api
  picarro_demo_idl
  picarro_core_io_idl
)

set(SOURCES
  translate-idl-demo.c++
)

### Recepies to build the library
include(BuildLibrary)
