# ----------------------------------
# Header
# ----------------------------------
cmake_minimum_required(VERSION 3.10)
project(JSON_example)

include(ExternalProject)
find_package(Git REQUIRED)

set(CMAKE_CXX_STANDARD 20)

# -------------------------------
# JSON
# -------------------------------
list(APPEND JSON_CMAKE_ARGS
    -DBUILD_TESTING=OFF
    -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}
)

ExternalProject_Add(
    json
    GIT_REPOSITORY https://hub.fastgit.org/nlohmann/json.git
    GIT_SHALLOW 1
    CMAKE_ARGS ${JSON_CMAKE_ARGS}
    PREFIX ${CMAKE_BINARY_DIR}/external/json/prefix
    TMP_DIR ${CMAKE_BINARY_DIR}/external/json/tmp
    STAMP_DIR ${CMAKE_BINARY_DIR}/external/json/stamp
    DOWNLOAD_DIR ${CMAKE_BINARY_DIR}/external/json/download
    SOURCE_DIR ${CMAKE_BINARY_DIR}/external/json/src
    BINARY_DIR ${CMAKE_BINARY_DIR}/external/json/build
    UPDATE_DISCONNECTED 1
)

# ----------------------------------
# Executable
# ----------------------------------
include_directories(${CMAKE_BINARY_DIR}/include)

add_executable(json_process_server ./src/json_process_server.cpp)
target_compile_definitions(json_process_server PUBLIC SERVER=1)
add_dependencies(json_process_server json)

add_executable(json_process_client ./src/json_process_client.cpp)
target_compile_definitions(json_process_client PUBLIC CLIENT=1)
add_dependencies(json_process_client json)