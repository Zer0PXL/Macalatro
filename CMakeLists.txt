cmake_minimum_required(VERSION 3.14)
project(Deckerz LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Deckerz/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Deckerz/*.hpp
)
add_executable(Deckerz ${SOURCES})
target_compile_definitions(Deckerz PRIVATE $<$<CONFIG:Debug>:DEBUG>)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(Deckerz PRIVATE sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_include_directories(Deckerz PRIVATE src)