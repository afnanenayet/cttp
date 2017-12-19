# cttp

[![Build Status](https://travis-ci.org/afnanenayet/cttp.svg?branch=master)](https://travis-ci.org/afnanenayet/cttp)

## Synopsis

`cttp` is a simple, static HTTP 1.1 server written in C. It was created for the sake of
personal edification. I used [RFC 2616](https://tools.ietf.org/html/rfc2616) and
the [Wikipedia page](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) as
references to help guide me in creating this project. I also drew inspiration from
this [reddit post](https://www.reddit.com/r/dailyprogrammer/comments/6lti17/20170707_challenge_322_hard_static_http_server/)

Right now, the project is stable. It has the basic functionality of an HTTP
server--it can serve websites from a given directory and serve different
types of files. However, it does not support serving binary files and is
currently single-threaded, making it very easy to DDOS.

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
more updated than Apple's provided binary for make. Use whatever version of
`make` you want.

You can also use the build script on a unix-like system if you have a `bash`
compatible shell installed. `cttp` relies on POSIX compliant behavior, so
it will not work on Windows.

### Testing

I have provided a script that will build the project and run unit tests via
CTest. Invoke it like so:

    ./build_test.sh

You can also use Cmake yourself:

    cmake . && make test

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
- 1: invalid arguments

Note that this program will follow symbolic links, both for requests and when
specifiying the base path in the arguments.

## Roadmap

[x] robust unit testing
[x] multiple MIME types
[] multithreading -- top priority at the moment
[] binary file support
