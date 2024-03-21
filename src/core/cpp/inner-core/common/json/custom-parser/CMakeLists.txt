## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PRIVATE
  tokenparser-base.c++
  tokenparser-stream.c++
  tokenparser-string.c++
  reader.c++
  writer.c++
)

