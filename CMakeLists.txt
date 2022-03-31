cmake_minimum_required(VERSION 3.0.0)
project(KIS_selection)

include_directories(app)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES src/suffix_automaton.cpp src/string_finder.cpp)
set(LIBRARY_NAME suffix_automaton)

add_library(${LIBRARY_NAME} OBJECT ${SOURCES})

target_include_directories(${LIBRARY_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(KIS_selection app/main.cpp)

target_link_libraries(KIS_selection PRIVATE ${LIBRARY_NAME})

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set_target_properties(
        ${LIBRARY_NAME} KIS_selection
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO
)
