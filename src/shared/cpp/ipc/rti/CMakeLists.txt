##
## -*- cmake -*-
#===============================================================================
## @file CMakeLists.txt
## @brief Build IDL encoder/decoder methods for share data types
## @author Tor Slettnes <tslettnes@picarro.com>
#===============================================================================

### RTI Data Distribution Service wrappers
add_subdirectory(dds)

### RTI IDL data type encoding/decoding
add_subdirectory(idl)

### Create interface library to encapsulate the above
set(TARGET picarro_shared_ipc_rti)
set(LIB_TYPE INTERFACE)
set(LIB_DEPS
  picarro_shared_ipc_rti_dds
  picarro_shared_ipc_rti_idl)

include(BuildLibrary)

