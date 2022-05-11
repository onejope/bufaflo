# CMakeList.txt : CMake project for TestApplication, include source and define
# project specific logic here.
#

# Run protoc on proto file
get_filename_component(echo_proto "echo.proto" ABSOLUTE)
get_filename_component(echo_proto_path "${echo_proto}" PATH)

set(echo_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.cc")
set(echo_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.h")
set(echo_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.cc")
set(echo_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.h")
set(echo_bufaflo_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.bufaflo.pb.cc")

add_custom_command(
      OUTPUT "${echo_proto_srcs}" "${echo_proto_hdrs}" "${echo_grpc_srcs}" "${echo_grpc_hdrs}" "${echo_bufaflo_srcs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        --bufaflo_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${echo_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        --plugin=protoc-gen-bufaflo="${_BUFAFLO_PLUGIN_EXECUTABLE}"
        --bufaflo_opt=echo.Echo_impl_header=echo_impl.h
        "${echo_proto}"
      DEPENDS "${echo_proto}" "${_BUFAFLO_PLUGIN_EXECUTABLE}")

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
add_executable (echo_server echo_server.cc echo_impl.h echo_impl.cc)
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

add_executable (echo_afl echo_afl.cc echo_impl.h echo_impl.cc)
target_link_libraries(echo_afl
  echo_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})

# Build the generated bufaflo code
add_executable (echo_bufaflo ${echo_bufaflo_srcs} echo_impl.h echo_impl.cc)
target_include_directories (echo_bufaflo PRIVATE ${echo_proto_path})
target_link_libraries(echo_bufaflo
  echo_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})
