cmake_minimum_required(VERSION 3.11)
project("gRPC Service")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(PROTOBUF REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG) 
find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(protobuflib proto/service.proto)
target_link_libraries(protobuflib gRPC::grpc++)

include_directories(protobuflib PUBLIC ${CMAKE_BINARY_DIR})
include_directories(header/server header/client header src)

protobuf_generate(TARGET protobuflib LANGUAGE cpp)
protobuf_generate(TARGET protobuflib LANGUAGE grpc
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=${CMAKE_SOURCE_DIR}/third_party/grpc/build/grpc_cpp_plugin")

set(SERVER_SOURCES
    src/server/main.cpp
    src/server/cachedStorage.cpp
    src/configParser.cpp
    src/server/grpcAuthService.cpp
)

set(CLIENT_SOURCES 
    src/client/client.cpp
    src/client/requestManager.cpp
    src/configParser.cpp
)

add_executable(myServer ${SERVER_SOURCES})
target_link_libraries(myServer protobuflib nlohmann_json::nlohmann_json)

add_executable(myClient ${CLIENT_SOURCES})
target_link_libraries(myClient protobuflib nlohmann_json::nlohmann_json)

add_custom_command(TARGET myServer POST_BUILD
    COMMAND cp ${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_CURRENT_BINARY_DIR}
)