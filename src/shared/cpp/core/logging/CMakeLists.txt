## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

target_sources(${TARGET} PUBLIC
  logging.c++
  dispatcher.c++
  sinks/rotatingpath.c++
  sinks/logsink.c++
  sinks/messagesink.c++
  sinks/logfilesink.c++
  sinks/jsonfilesink.c++
  sinks/streamsink.c++
)

add_subdirectory(message)
add_subdirectory(sinks)
