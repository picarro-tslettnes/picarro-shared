## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

if(BUILD_PYTHON_CPP)
  add_subdirectory(base)
  add_subdirectory(embedded)

  set(TARGET picarro_shared_ipc_python)
  set(LIB_TYPE INTERFACE)
  set(LIB_DEPS
    picarro_shared_ipc_python_base
    picarro_shared_ipc_python_embedded
  )
  include(BuildLibrary)

endif()

