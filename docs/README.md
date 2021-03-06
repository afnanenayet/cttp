# cttp

[![Build Status](https://travis-ci.org/afnanenayet/cttp.svg?branch=master)](https://travis-ci.org/afnanenayet/cttp)

## Synopsis

`cttp` is a multithreaded, static HTTP 1.1 server written in C. It was created
for the sake of personal edification. I used
[RFC 2616](https://tools.ietf.org/html/rfc2616) and
the [Wikipedia page](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) as
references to help guide me in creating this project. I also drew inspiration from
this
[reddit post](https://www.reddit.com/r/dailyprogrammer/comments/6lti17/20170707_challenge_322_hard_static_http_server/)

Right now, the project is stable. It has the basic functionality of an HTTP
server--it can serve websites from a given directory and serve different
types of files. `cttp` does not support serving binary files (yet).

### Structure

This project has the following hierarchy:

```
cttp
├── docs
├── include
├── src
└── test
```

The generated binary gets placed in a folder called `bin`

## Development

This project is written using standard C11. The git workflow is managed
through [git-flow](https://github.com/nvie/gitflow/). The build system
uses `cmake` for compilation as well as testing, and I am using
[cmocka](https://cmocka.org) as the framework for unit testing.

### Compilation

This project uses `cmake` for compilation. In order to compile the project
you can either run the build script which will
automatically try to invoke gmake on MacOS since the binary shipped by Apple
is older.

    ./build.sh
    cmake . && make

I run `cmake . && gmake` on MacOS because my version of GNU make tends to be
more updated than Apple's provided binary for make. Use whatever build system
you want.

You can also use the build script on a unix-like system if you have a `bash`
compatible shell installed. `cttp` relies on POSIX APIs, so
it will not work on Windows.

### Testing

I have provided a script that will build the project and run unit tests via
CMocka. In order to build tests, you need to set CMake to build in debug mode.

    cmake -DCMAKE_RELEASE_TYPE=Debug . && make test

or

    cmake . && ctest --verbose

These will run unit the tests and display test output to STDOUT.

## Usage

`cttp -p [port] -r [base path]`

- `-p`: the port that the HTTP server will be deployed to. It is optional,
and defaults to port `8080`
- `-r`: the base path to serve files from. This must be a valid file and is
required.

### Return codes

- 0: success/no errors
- 1: invalid arguments/generic argument error
- 2: networking error
- 3: unknown error

Note that this program will follow symbolic links, both for requests and when
specifiying the base path in the arguments.

## Roadmap

- [x] robust unit testing
- [x] multiple MIME types
- [x] multithreading
- [ ] better DDOS protection (limiting threadpools, blocking rapid repeated
connections)
- [ ] binary file support
