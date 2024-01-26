## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PUBLIC
  level.c++
  domain.c++
  flow.c++
  event.c++
  exceptions.c++
)
