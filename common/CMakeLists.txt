add_library(common INTERFACE)

# Tell any target that links 'common' to look in the current directory for headers
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})