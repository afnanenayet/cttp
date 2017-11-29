# build file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.9)
project(cttp C)

# Output to certain folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(include)
file(GLOB sources "src/*.c")
add_executable(cttp ${sources})
