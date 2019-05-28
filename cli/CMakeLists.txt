cmake_minimum_required(VERSION 3.7)

# compiler options
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

project(json-analyzer)

find_library(JSON_STREAM_ANALYZER libjson-stream-analyzer.a)
message(STATUS "Found json-stream-analyzer library: ${JSON_STREAM_ANALYZER}")

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${JSON_STREAM_ANALYZER}")

add_executable(json-analyzer main.cpp)

target_link_libraries(json-analyzer
    ${JSON_STREAM_ANALYZER}
    ${IO_BUFFER}
)
