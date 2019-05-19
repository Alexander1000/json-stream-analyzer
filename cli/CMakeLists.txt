cmake_minimum_required(VERSION 3.7)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
set(CMAKE_CXX_STANDARD 17)

# compiler options
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(json-analyzer)

include_directories(../include)

find_library(JSON_STREAM_ANALYZER libjson-stream-analyzer.dylib PATHS .. NO_DEFAULT_PATH)
message(STATUS "Found json-stream-analyzer library: ${JSON_STREAM_ANALYZER}")

add_executable(json-analyzer main.cpp)

target_link_libraries(json-analyzer
    ${JSON_STREAM_ANALYZER}
)
