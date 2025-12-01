add_executable(Day02 main.cpp)

# Link the shared utilities
target_link_libraries(Day02 PUBLIC common)

# Optional: Copy input.txt to the build directory automatically
configure_file(input.txt input.txt COPYONLY)
configure_file(input-2.txt input-2.txt COPYONLY)
