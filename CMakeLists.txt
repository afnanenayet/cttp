# build file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.2)
project(cttp C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
# Output to certain folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_GROUP production CACHE_STRING "build target")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -fsanitize=address -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

# files included in both prod and testing
# add_subdirectory(src)

#if(TARGET_GROUP STREQUAL release)
    # put files and do things that are strictly for release
    #elseif(TARGET_GROUP STREQUAL test)
    #include(CTest)
    # TODO finish integrating Unity test suite
    #endif()

include_directories(include)
file(GLOB sources "src/*.c")
add_executable(cttp ${sources})
set_property(TARGET cttp PROPERTY C_STANDARD 11)
