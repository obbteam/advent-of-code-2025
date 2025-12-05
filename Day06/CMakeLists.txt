add_executable(Day06 main.cpp
        part1/part1.cpp
        part2/part2.cpp)

# Link the shared utilities
target_link_libraries(Day06 PUBLIC common)

# Optional: Copy input.txt to the build directory automatically
configure_file(input.txt input.txt COPYONLY)
configure_file(input-2.txt input-2.txt COPYONLY)
