cmake_minimum_required(VERSION 3.10)
project(AdventOfCode2025)

set(CMAKE_CXX_STANDARD 20)

# --- Z3 Setup ---
# Tries to find Z3Config.cmake
find_package(Z3 REQUIRED)

add_executable(Day10 main.cpp
        part1/part1.cpp
        part2/part2.cpp)

# Link common utilities
target_link_libraries(Day10 PUBLIC common)

# --- Link Z3 ---
if(TARGET z3::libz3)
    # Modern CMake approach (standard on Mac/Linux usually)
    target_link_libraries(Day10 PRIVATE z3::libz3)
else()
    # Fallback for older Z3 configurations
    target_include_directories(Day10 PRIVATE ${Z3_CXX_INCLUDE_DIRS})
    target_link_libraries(Day10 PRIVATE ${Z3_LIBRARIES})
endif()

# Copy inputs
configure_file(input.txt input.txt COPYONLY)
configure_file(input-2.txt input-2.txt COPYONLY)