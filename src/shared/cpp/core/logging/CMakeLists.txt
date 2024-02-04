## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PRIVATE
  logging.c++
)

add_subdirectory(message)
add_subdirectory(sinks)
add_subdirectory(dispatchers)
