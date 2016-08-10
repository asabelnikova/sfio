cmake_minimum_required(VERSION 3.0.2)
set(PROJECT_NAME_STR sfio)
set(EXEC_NAME sfio)

project (sfio C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SOURCES_DIR ${sfio_SOURCE_DIR}/server)
set(PROTO_DIR ${sfio_SOURCE_DIR}/proto)
set(Boost_USE_STATIC_LIBS ON)

find_package(websocketpp REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(Boost COMPONENTS filesystem system program_options REQUIRED)
find_package(Protobuf REQUIRED)

file(GLOB SOURCES ${SOURCES_DIR}/*.cpp)


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
add_subdirectory(proto)
add_subdirectory(server)

