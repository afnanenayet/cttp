# build file for cttp
# Afnan Enayet

cmake_minimum_required(VERSION 3.2)
project(cttp C)

# Output to certain folders
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(TARGET_GROUP production CACHE_STRING "build target")

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
