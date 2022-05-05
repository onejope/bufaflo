# CMakeList.txt : CMake project for TestApplication, include source and define
# project specific logic here.
#

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
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

# Run protoc on proto file
get_filename_component(echo_proto "echo.proto" ABSOLUTE)
get_filename_component(echo_proto_path "${echo_proto}" PATH)

set(echo_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.cc")
set(echo_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.h")
set(echo_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.cc")
set(echo_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.h")

add_custom_command(
      OUTPUT "${echo_proto_srcs}" "${echo_proto_hdrs}" "${echo_grpc_srcs}" "${echo_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${echo_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${echo_proto}"
      DEPENDS "${echo_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_library(echo_grpc_proto
  ${echo_grpc_srcs}
  ${echo_grpc_hdrs}
  ${echo_proto_srcs}
  ${echo_proto_hdrs})
target_link_libraries(echo_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Add source to this project's executable.
add_executable (echo_server echo_server.cc)
target_link_libraries(echo_server
  echo_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

add_executable (echo_client echo_client.cc)
target_link_libraries(echo_client
  echo_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# TODO: Add tests and install targets if needed.
