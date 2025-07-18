cmake_minimum_required(VERSION 3.14)
project(Macalatro LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optionally set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find all source files recursively
file(GLOB_RECURSE MACALATRO_SOURCES
    Macalatro/*.cpp
    Macalatro/*.cxx
    Macalatro/*.cc
    Macalatro/*.c
)

file(GLOB_RECURSE MACALATRO_HEADERS
    Macalatro/*.h
    Macalatro/*.hpp
)

# Optionally include headers for IDEs
add_executable(Macalatro ${MACALATRO_SOURCES} ${MACALATRO_HEADERS})

# Include directories
target_include_directories(Macalatro PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries (add any dependencies here)
# target_link_libraries(Macalatro PRIVATE ...)

# Enable warnings (GCC/Clang/MSVC)
if (MSVC)
    target_compile_options(Macalatro PRIVATE /W4)
else()
    target_compile_options(Macalatro PRIVATE -Wall -Wextra -pedantic)
endif()

# Optionally add install rules
install(TARGETS Macalatro RUNTIME DESTINATION bin)
