# build file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.2)
project(cttp C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
set(program_name cttp)
include(CTest)

# Output to certain folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_GROUP production CACHE_STRING "build target")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fsanitize=address -g -std=c11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -std=c11")

enable_testing()
add_subdirectory(test)
include_directories(include)

file(GLOB sources "src/*.c")
add_executable(${program_name} ${sources})
target_link_libraries(${program_name} m)
set_property(TARGET ${program_name} PROPERTY C_STANDARD 11)

list(REMOVE_ITEM sources ${PROJECT_SOURCE_DIR}/src/cttp.c)
add_library(cttpfn ${sources})
set_property(TARGET cttpfn PROPERTY C_STANDARD 11)
