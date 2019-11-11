cmake_minimum_required(VERSION 3.0)
project(RobocupProtocol)

# We need protobuf to generate the messages
find_package(Protobuf REQUIRED)

# Build our protobuf classes
file(GLOB_RECURSE protos "${CMAKE_CURRENT_SOURCE_DIR}/**.proto")
message(STATUS ${protos})
foreach(proto ${protos})
  # Get the file without the extension
  get_filename_component(file_we ${proto} NAME_WE)

  # Run the protocol buffer compiler on the builtin protocol buffers
  add_custom_command(OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.cc"
                            "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.h"
                     COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
                             ARGS
                             --cpp_out=lite:${CMAKE_CURRENT_BINARY_DIR}
                             -I${CMAKE_CURRENT_SOURCE_DIR}
                             "${CMAKE_CURRENT_SOURCE_DIR}/${file_we}.proto"
                     DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${file_we}.proto"
                     COMMENT "Compiling protocol buffer ${proto}")

  set(proto_src ${proto_src} "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.cc"
                "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.h")

  set_source_files_properties(
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.proto"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.cc"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.pb.h"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.py.cpp"
    "${CMAKE_CURRENT_BINARY_DIR}/${file_we}.h"
    PROPERTIES
    GENERATED
    TRUE
    # Prevent Effective C++ and unused parameter error checks being performed on
    # generated files.
    COMPILE_FLAGS "-Wno-unused-parameter -Wno-error=unused-parameter -Wno-error"
    )

endforeach(proto)

add_executable(protocol example.cpp ${proto_src})
target_include_directories(protocol PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(protocol protobuf::libprotobuf protobuf::libprotobuf-lite)
