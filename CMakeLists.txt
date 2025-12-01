cmake_minimum_required(VERSION 4.0)
project(advent_of_code_2025)

set(CMAKE_CXX_STANDARD 20)

# Add the common utility library
add_subdirectory(common)

# Add days (Uncomment these as you progress)
add_subdirectory(Day01)
add_subdirectory(Day02)
#add_subdirectory(Day03)

