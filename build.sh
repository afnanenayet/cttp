# build script for cttp
# will build with gmake if on OSX since the distributed make binary is fairly
# old

platform="unknown"
uname_str="$(uname)"
make="make"

# Check to see if user has cmake installed
# otherwise print error and exit
if ! [ -x "$(command -v cmake)" ] ; then
    echo >&2 "cttp requires cmake to build"
    exit 1
fi

# Building for MacOS/OS X, try to use GNU make if the user has it installed
# otherwise fall back to the older, bundled make
if [ "$uname_str" == "Darwin" ] && [ -x "$(command -v gmake)" ]; then
    make="gmake"
fi

echo "Building cttp for platform $uname_str with $make"
cmake . && make
