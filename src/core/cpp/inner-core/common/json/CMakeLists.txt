## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PRIVATE
  jsondecoder.c++
  jsonreader.c++)

target_compile_definitions(${TARGET} PUBLIC RAPIDJSON_HAS_STDSTRING)

