## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build Picarro static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

# Set build version, date and time
configure_file(buildinfo.h.in buildinfo.h)
target_include_directories(${TARGET} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
