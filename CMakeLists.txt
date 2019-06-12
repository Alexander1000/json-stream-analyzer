cmake_minimum_required(VERSION 3.7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

set(JSON_STREAM_ANALYZER_SOURCES
    src/object/element.cpp
    src/tokens/token.cpp
    src/tokens/token_array_close.cpp
    src/tokens/token_array_open.cpp
    src/tokens/token_braces_close.cpp
    src/tokens/token_braces_open.cpp
    src/tokens/token_colon.cpp
    src/tokens/token_comma.cpp
    src/tokens/token_lexeme_word.cpp
    src/tokens/token_numeric.cpp
    src/tokens/token_quotes.cpp
    src/tokens/token_bool.cpp
    src/tokens/token_null.cpp
    src/exceptions.cpp
    src/decoder.cpp
    src/stream.cpp
)

if(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
    set(CMAKE_INSTALL_INCLUDEDIR include)
endif(NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)

# installation of json-stream-analyzer CXX library headers
install(DIRECTORY include/json-stream-analyzer DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#--------------
# Static
#--------------

project(json-stream-analyzer VERSION 0.3.0 DESCRIPTION "json stream analyzer")

add_library(${PROJECT_NAME} STATIC ${JSON_STREAM_ANALYZER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/json-stream-analyzer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "json-stream-analyzer")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS -fPIC)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

target_link_libraries(${PROJECT_NAME} ${IO_BUFFER})

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)

#--------------
# Shared
#--------------

project(json-stream-analyzer-shared VERSION 0.3.0 DESCRIPTION "json stream analyzer")

add_library(${PROJECT_NAME} SHARED ${JSON_STREAM_ANALYZER_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/json-stream-analyzer.h)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "json-stream-analyzer")

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE src)

find_library(IO_BUFFER libio-buffer.a)
message(STATUS "Found io-buffer library: ${IO_BUFFER}")

target_link_libraries(${PROJECT_NAME} ${IO_BUFFER})

install (TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT library
)
