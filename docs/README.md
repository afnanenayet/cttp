# cttp

[![Build Status](https://travis-ci.org/afnanenayet/cttp.svg?branch=master)](https://travis-ci.org/afnanenayet/cttp)

## Synopsis

`cttp` is a simple, static HTTP 1.1 server written in C. It was created for the sake of
personal edification. I used [RFC 2616](https://tools.ietf.org/html/rfc2616) and
the [Wikipedia page](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) as
references to help guide me in creating this project. I also drew inspiration from
this [reddit post](https://www.reddit.com/r/dailyprogrammer/comments/6lti17/20170707_challenge_322_hard_static_http_server/)

### Structure

This project has the following hierarchy:

```
cttp
├── docs
├── include
├── src
└── test
```

The binary gets placed in a folder called `bin`

## Compilation

This project is written in C and uses `cmake` for compilation. In
order to compile the project you can either run the build script which will
automatically try to invoke gmake since it's more recent.

    ./build.sh
    cmake . && make

I run `cmake . && gmake` on MacOS because my version of GNU make tends to be
more updated than Apple's provided binary for make. Use whatever version of
`make` you want.

You can also use the build script on a unix-like system if you have a `bash`
compatible shell
installed. I haven't tested this project on Windows, but it is compiled
using the clang C compiler, using strict C11. Since CMake is cross-platform,
`cttp` should compile on Windows, but it is not tested and I make no promises.

This project uses [cmocka](https://cmocka.org) for unit testing.

## Usage

`cttp -p [port] -r [base path]`

- `-p`: the port that the HTTP server will be deployed to. It is optional,
and defaults to port `8080`
- `-r`: the base path to serve files from. This must be a valid file and is
a required argument.

### Return codes

- 0: success/no errors
- 1: invalid arguments

Note that this program will follow symbolic links, both for requests and when
specifiying the base path in the arguments.
