## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PRIVATE
  tokenparser.c++
  jsonparser.c++
  jsonreader.c++

  jsonbuilder.c++
  jsonwriter.c++
)

