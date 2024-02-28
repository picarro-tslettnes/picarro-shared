## -*- cmake -*-
#===============================================================================
## @file Findgrpc.cmake
## @brief CMake method to generate gRPC bindings for C++ and Python
##
## Modeled after
##  - https://github.com/IvanSafonov/grpc-cmake-example/blob/master/cmake/FindGRPC.cmake
##  - https://github.com/zhengwx11/FindGRPC/blob/master/FindGRPC.cmake
##
## @copyright 2019 Tor Slettnes <tor@slett.net>
## @copyright 2017 Wenxun Zheng <zhengwx11@foxmail.com>
## @copyright 2009 Kitware, Inc.
## @copyright 2009-2011 Philip Lowman <philip@yhbt.com>
## @copyright 2008 Esben Mose Hansen, Ange Optimization ApS
##
## Distributed under the OSI-approved BSD License:
##
## 1. Redistributions of source code must retain
##    the above copyright notice, this list of conditions
##    and the following disclaimer.
## 2. Redistributions in binary form must reproduce the above
##    copyright notice, this list of conditions and the following
##    disclaimer in the documentation and/or other materials provided
##    with the distribution.
## 3. Neither the name of the copyright holder nor the names of its
##    contributors may be used to endorse or promote products derived
##    from this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
## "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
## TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
## PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER
## OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
## EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
## PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
## PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
## LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
## NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
## SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
##
## This software is distributed WITHOUT ANY WARRANTY; without even the
## implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
##==============================================================================

#
# Locate and configure the gRPC library
#
# Adds the following targets:
#
#  gRPC::grpc - gRPC library
#  gRPC::grpc++ - gRPC C++ library
#  gRPC::grpc++_reflection - gRPC C++ reflection library
#  gRPC::grpc_cpp_plugin - C++ generator plugin for Protocol Buffers
#

#
# Generates C++ sources from the .proto files
#
# grpc_generate_cpp (<SRCS> <HDRS> <DEST> [<ARGN>...])
#
#  SRCS - variable in which autogenerated source files will be listed
#  HDRS - variable in which autogenerated header files will be listed
#  DEST - directory where the source files will be created
#  ARGN - .proto files
#

# gRPC always requires Thread support.
find_package(Threads REQUIRED)


function(GRPC_GENERATE_CPP SRCS HDRS DEST)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GRPC_GENERATE_CPP() called without any proto files")
    return()
  endif()

  if(GRPC_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(ABS_PATH ${ABS_FIL} DIRECTORY)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  else()
    set(_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(DIR ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  endif()

  set(${SRCS})
  set(${HDRS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)

    list(APPEND ${SRCS} "${DEST}/${FIL_WE}.grpc.pb.cc")
    list(APPEND ${HDRS} "${DEST}/${FIL_WE}.grpc.pb.h")
    add_custom_command(
      OUTPUT "${DEST}/${FIL_WE}.grpc.pb.cc"
             "${DEST}/${FIL_WE}.grpc.pb.h"
      COMMAND protobuf::protoc
      ARGS --grpc_out ${DEST} ${_protobuf_include_path} --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN} ${ABS_FIL}
      DEPENDS ${ABS_FIL} protobuf::protoc gRPC::grpc_cpp_plugin
      COMMENT "Running cpp gRPC compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set_source_files_properties(${${SRCS}} ${${HDRS}} PROPERTIES GENERATED TRUE)
  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
  set(${HDRS} ${${HDRS}} PARENT_SCOPE)
endfunction()


#
# Generates Python sources from the .proto files
#
# grpc_generate_python (<SRCS> <DEST> <ARGN>...)
#
#  SRCS - variable to define with autogenerated source files
#  DEST - directory where the source files will be created
#  ARGN - .proto files
#

function(GRPC_GENERATE_PYTHON SRCS DEST)
  if(NOT ARGN)
    message(SEND_ERROR "Error: GRPC_GENERATE_PYTHON() called without any proto files")
    return()
  endif()

  if(GRPC_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach(FIL ${ARGN})
      get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component(ABS_PATH ${ABS_FIL} DIRECTORY)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  else()
    set(_protobuf_include_path)
  endif()

  if(DEFINED PROTOBUF_IMPORT_DIRS)
    foreach(DIR ${PROTOBUF_IMPORT_DIRS})
      get_filename_component(ABS_PATH ${DIR} ABSOLUTE)
      list(FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if(${_contains_already} EQUAL -1)
          list(APPEND _protobuf_include_path -I ${ABS_PATH})
      endif()
    endforeach()
  endif()

  set(${SRCS})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    #get_filename_component(FIL_DIR ${ABS_FIL} DIRECTORY)

    set(GEN_FIL "${DEST}/${FIL_WE}_pb2_grpc.py")
    #list(APPEND _protobuf_include_path -I ${FIL_DIR})
    list(APPEND ${SRCS} "${GEN_FIL}")

    add_custom_command(
      OUTPUT "${GEN_FIL}"
      COMMAND protobuf::protoc
      ARGS --grpc_out ${DEST} ${_protobuf_include_path} --plugin=protoc-gen-grpc=${GRPC_PYTHON_PLUGIN} ${ABS_FIL}
      DEPENDS ${ABS_FIL} protobuf::protoc gRPC::grpc_python_plugin
      COMMENT "Running Python gRPC compiler on ${FIL}"
      VERBATIM )
  endforeach()

  set(${SRCS} ${${SRCS}} PARENT_SCOPE)
endfunction()


# By default have GRPC_GENERATE_CPP macro pass -I to protoc
# for each directory where a proto file is referenced.
if(NOT DEFINED GRPC_GENERATE_CPP_APPEND_PATH)
  set(GRPC_GENERATE_CPP_APPEND_PATH TRUE)
endif()

# Find gRPC include directory
find_path(GRPC_INCLUDE_DIR grpc/grpc.h)
mark_as_advanced(GRPC_INCLUDE_DIR)

# Find gRPC library
find_library(GRPC_LIBRARY NAMES grpc)
mark_as_advanced(GRPC_LIBRARY)
add_library(gRPC::grpc UNKNOWN IMPORTED)
set_target_properties(gRPC::grpc PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${GRPC_INCLUDE_DIR}
    INTERFACE_LINK_LIBRARIES Threads::Threads #"-lpthread;-ldl"
    IMPORTED_LOCATION ${GRPC_LIBRARY}
)

# Find gRPC C++ library
find_library(GRPC_GRPC++_LIBRARY NAMES grpc++)
mark_as_advanced(GRPC_GRPC++_LIBRARY)
add_library(gRPC::grpc++ UNKNOWN IMPORTED)
set_target_properties(gRPC::grpc++ PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${GRPC_INCLUDE_DIR}
    INTERFACE_LINK_LIBRARIES gRPC::grpc
    IMPORTED_LOCATION ${GRPC_GRPC++_LIBRARY}
)

# Find gRPC C++ reflection library
find_library(GRPC_GRPC++_REFLECTION_LIBRARY NAMES grpc++_reflection)
mark_as_advanced(GRPC_GRPC++_REFLECTION_LIBRARY)
add_library(gRPC::grpc++_reflection UNKNOWN IMPORTED)
set_target_properties(gRPC::grpc++_reflection PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${GRPC_INCLUDE_DIR}
    INTERFACE_LINK_LIBRARIES gRPC::grpc++
    IMPORTED_LOCATION ${GRPC_GRPC++_REFLECTION_LIBRARY}
)

# Find gRPC CPP generator
find_program(GRPC_CPP_PLUGIN NAMES grpc_cpp_plugin)
mark_as_advanced(GRPC_CPP_PLUGIN)
add_executable(gRPC::grpc_cpp_plugin IMPORTED)
set_target_properties(gRPC::grpc_cpp_plugin PROPERTIES
    IMPORTED_LOCATION ${GRPC_CPP_PLUGIN}
)

# Find gRPC Python generator
find_program(GRPC_PYTHON_PLUGIN NAMES grpc_python_plugin)
mark_as_advanced(GRPC_PYTHON_PLUGIN)
add_executable(gRPC::grpc_python_plugin IMPORTED)
set_target_properties(gRPC::grpc_python_plugin PROPERTIES
    IMPORTED_LOCATION ${GRPC_PYTHON_PLUGIN}
)

# Update *_FOUND variables based on results above
include(${CMAKE_ROOT}/Modules/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(grpc
  DEFAULT_MSG GRPC_LIBRARY GRPC_INCLUDE_DIR GRPC_GRPC++_REFLECTION_LIBRARY
  GRPC_CPP_PLUGIN GRPC_PYTHON_PLUGIN)
