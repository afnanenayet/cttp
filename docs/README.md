# cttp

## Synopsis

`cttp` is a simple HTTP 1.0 server written in C. It was created for the sake of
personal edification.

## Compilation

This project is written in C and uses `CMake` for basic compilation. In
order to compile the project:

    cmake . && make

I run `cmake . && gmake` on MacOS because my version of GNU make tends to be
more updated than Apple's provided binary for make.

You can also use the build script on a unix-like system if you have `bash`
installed. I haven't tested this project on Windows, but it is compiled
using the clang C compiler, using strict C11. Since CMake is cross-platform,
I'd imagine that `cttp` should compile on Windows.

