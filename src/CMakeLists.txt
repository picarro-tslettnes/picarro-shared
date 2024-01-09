##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description CMake rules to build static/shared library
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### Build shared libraries
add_subdirectory(shared)

### Build common applications
add_subdirectory(apps)

### Build product-specific components
add_subdirectory(products)
