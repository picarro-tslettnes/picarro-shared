##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(shell)

### Install "settings/" folder as data
install(DIRECTORY settings TYPE DATA)
