## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @description Demo application interface - DDS implementation
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

add_subdirectory(types)

### Pub/Sub interface
add_subdirectory(dds-publisher)
add_subdirectory(dds-subscriber)

### RPC interface
add_subdirectory(rpc-client)
add_subdirectory(rpc-server)
