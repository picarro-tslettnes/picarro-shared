## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Name of this library.
set(TARGET picarro_shared_messaging_zmq_pypickle)

### Library type
set(LIB_TYPE STATIC)

### Library dependencies.
set(LIB_DEPS
  picarro_shared_messaging_zmq_base
  picarro_shared_messaging_python
)

### Source files in this folder
set(SOURCES
)

### Recepies to build the library
include(BuildLibrary)

