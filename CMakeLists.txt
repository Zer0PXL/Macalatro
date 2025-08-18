cmake_minimum_required(VERSION 3.14)
project(Macalatro LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Macalatro/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Macalatro/*.hpp
)
add_executable(Macalatro ${SOURCES})
target_compile_definitions(Macalatro PRIVATE $<$<CONFIG:Debug>:DEBUG>)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(Macalatro PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_include_directories(Macalatro PRIVATE src)