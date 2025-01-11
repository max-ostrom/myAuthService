cmake_minimum_required(VERSION 3.11)
project("Auth Service")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(PROTOBUF REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG) 
find_package(Boost REQUIRED COMPONENTS program_options)
find_package(OpenSSL REQUIRED)

add_library(protobuflib proto/service.proto)
target_link_libraries(protobuflib gRPC::grpc++)

include_directories(protobuflib PUBLIC ${CMAKE_BINARY_DIR})
include_directories(header/server header/client header src)

protobuf_generate(TARGET protobuflib LANGUAGE cpp)
protobuf_generate(TARGET protobuflib LANGUAGE grpc
GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
PLUGIN "protoc-gen-grpc=${CMAKE_SOURCE_DIR}/third_party/grpc/build/grpc_cpp_plugin")

set(SERVER_HEADERS
    header/dataProvider/idataprovider.h
    header/server/cachedstorage.h
    header/server/grpcauthserviceimpl.h
    header/server/itokengenerator.h
    header/server/tokengenerator.h
    header/server/ihasher.h
    header/server/shahasher.h
)

set(CLIENT_HEADERS
    header/client/irequestmanager.h
    header/client/requestmanager.h
)

set(COMMON_HEADERS
    header/status.h
    header/logger.h
)

set(SERVER_SOURCES
    src/server/main.cpp
    src/server/cachedstorage.cpp
    src/server/grpcauthserviceimpl.cpp
)

set(CLIENT_SOURCES 
    src/client/client.cpp
    src/client/requestmanager.cpp
)

set(COMMON_SOURCES 
    
)

add_executable(AuthService ${SERVER_SOURCES} ${COMMON_SOURCES} ${SERVER_HEADERS} ${COMMON_HEADERS})
target_link_libraries(AuthService protobuflib Boost::program_options OpenSSL::SSL OpenSSL::Crypto)

add_executable(testClient ${CLIENT_SOURCES} ${COMMON_SOURCES} ${CLIENT_HEADERS} ${COMMON_HEADERS})
target_link_libraries(testClient protobuflib)

# make installer
# make lite version without boost & json