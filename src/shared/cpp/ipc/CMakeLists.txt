## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Abstract service interface, agnostic to communications bus
add_subdirectory(api)
add_subdirectory(dds)
add_subdirectory(google)
