##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PUBLIC
  rotatingpath.c++
  logsink.c++
  messagesink.c++
  logfilesink.c++
  jsonfilesink.c++
  streamsink.c++
)
