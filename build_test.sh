# build_test.sh
# builds cttp binary and library and uses ctest to execute unit tests

./build.sh && ctest --verbose
