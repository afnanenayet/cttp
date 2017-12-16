# CMakeLists.txt for testing subdirectory for cttp
cmake_minimum_required(VERSION 3.0)

set(TEST_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test)

include_directories(
    "${PROJECT_SOURCE_DIR}/include"
)

add_executable(file_dispatch_test file_dispatch_test.c)
add_dependencies(file_dispatch_test file_dispatch_test)
add_test(NAME file_dispatch_test COMMAND file_dispatch_test WORKING_DIRECTORY ${TEST_OUTPUT_DIR})
target_link_libraries(file_dispatch_test cttpfn cmocka)

set_target_properties(
    file_dispatch_test
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${TEST_OUTPUT_DIR}
)
