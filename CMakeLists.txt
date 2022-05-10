# CMakeList.txt : CMake project for bufaflo, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13)

project ("bufaflo")

# Setup gRPC
include(FetchContent)
FetchContent_Declare(
  gRPC
  GIT_REPOSITORY https://github.com/grpc/grpc
  GIT_TAG        v1.45.2  # e.g v1.28.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_PROTOBUF_LIBPROTOC libprotoc)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

# Add subdirectories.
add_subdirectory (bufaflo)
set(_BUFAFLO_PLUGIN_EXECUTABLE $<TARGET_FILE:bufaflo>)

add_subdirectory (TestApplication)
