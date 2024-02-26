##
## -*- cmake -*-
#===============================================================================
## @brief CMake recipes for building a project
#===============================================================================

if(NOT PROJECT_INCLUDED)
  SET(PROJECT_INCLUDED true)

  if(WIN32)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
  endif()

  ### C++ compiler features
  # set(CMAKE_CXX_STANDARD 20)
  # set(CMAKE_CXX_STANDARD_REQUIRED ON)
  # set(CMAKE_CXX_EXTENSIONS OFF)

  ### Source additional files from this folder
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

  ### Where to find custom build scripts
  set(BUILD_SCRIPTS_DIR "${CMAKE_CURRENT_LIST_DIR}/../scripts")

  # set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/out/install/${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})

  ### Include rules to build doxygen
  include(Doxygen)
endif()
