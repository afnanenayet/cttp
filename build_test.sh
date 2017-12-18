# build_test.sh
# builds cttp binary and library and uses ctest to execute unit tests

./build.sh && env CTEST_OUTPUT_ON_FAILURE=1 make -j test
