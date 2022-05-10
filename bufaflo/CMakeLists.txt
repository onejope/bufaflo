# CMakeList.txt : CMake project for bufaflo, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (bufaflo "bufaflo.cpp" )
target_link_libraries(bufaflo
  ${_PROTOBUF_LIBPROTOBUF}
  ${_PROTOBUF_LIBPROTOC})


