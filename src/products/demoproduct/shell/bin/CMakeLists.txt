## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief CMake recipe to install binary scripts
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

cmake_minimum_required(VERSION 3.14)

if (BUILD_PYTHON)
  set(SOURCES shell)
  install(PROGRAMS ${SOURCES} TYPE BIN)
endif()
