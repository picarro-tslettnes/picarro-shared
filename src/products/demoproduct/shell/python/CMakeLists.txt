##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief CMake recipe to install Python components
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Modules to be installed as programs, with execute permissionss
set(PROGRAMS
  demoshell.py
)

### Modules to be installed as supporting files, without execute permissions
set(FILES
)

### Subdirectories
set(DIRECTORIES
)

include(BuildPython)
