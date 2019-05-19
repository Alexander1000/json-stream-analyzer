cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_EXTENSIONS OFF)

set(JSON_STREAM_ANALYZER_SOURCES
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

#--------------
# Static
#--------------

project(json-stream-analyzer VERSION 0.0.1 DESCRIPTION "json stream analyzer")

add_library(${PROJECT_NAME} STATIC ${JSON_STREAM_ANALYZER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/json-stream-analyzer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "json-stream-analyzer")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)

#--------------
# Shared
#--------------

project(json-stream-analyzer-shared VERSION 0.0.1 DESCRIPTION "json stream analyzer")

add_library(${PROJECT_NAME} SHARED ${JSON_STREAM_ANALYZER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/json-stream-analyzer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "json-stream-analyzer")

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)
