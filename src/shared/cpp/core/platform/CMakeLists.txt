## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PRIVATE
  path.c++
  symbols.c++
  timezone.c++
  process.c++
  runtime.c++
  systemservice.c++
  logsink.c++
)
