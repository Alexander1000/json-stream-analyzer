cmake_minimum_required(VERSION 3.7)

project(json-stream-analyzer VERSION 0.0.1 DESCRIPTION "json stream analyzer")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
set(CMAKE_CXX_STANDARD 17)

# compiler options
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(json-stream-analyzer SHARED
    src/json/object/element.cpp
    src/json/tokens/token.cpp
    src/json/tokens/token_array_close.cpp
    src/json/tokens/token_array_open.cpp
    src/json/tokens/token_braces_close.cpp
    src/json/tokens/token_braces_close.cpp
    src/json/tokens/token_colon.cpp
    src/json/tokens/token_comma.cpp
    src/json/tokens/token_lexeme_word.cpp
    src/json/tokens/token_numeric.cpp
    src/json/tokens/token_quotes.cpp
    src/json/decoder.cpp
    src/json/stream.cpp
    src/buffer/io_buffer.cpp
    src/buffer/io_file_reader.cpp
    src/buffer/io_memory_buffer.cpp
)

set_target_properties(json-stream-analyzer PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(json-stream-analyzer PROPERTIES SOVERSION 1)

set_target_properties(json-stream-analyzer PROPERTIES PUBLIC_HEADER include/json-stream-analyzer.h)

target_include_directories(json-stream-analyzer PRIVATE include)
target_include_directories(json-stream-analyzer PRIVATE src)

#project(json-analyzer)
#
#include_directories(
#    include
#)
#
#find_library(JSON_STREAM_ANALYZER libjson-stream-analyzer.dylib PATHS . NO_DEFAULT_PATH)
#message(STATUS "Found json-stream-analyzer library: ${JSON_STREAM_ANALYZER}")
#
#add_executable(json-analyzer src/main.cpp)
#
#target_link_libraries(json-analyzer
#    ${JSON_STREAM_ANALYZER}
#)
