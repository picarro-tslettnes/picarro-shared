## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(core)    # Shared components (modules, libraries)
add_subdirectory(mantle)  # Common applications/microservices
add_subdirectory(crust)   # Deployments: project settings, scripts, ...
