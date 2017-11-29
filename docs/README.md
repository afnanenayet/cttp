# cttp

## Synopsis

`cttp` is a simple, static HTTP 1.1 server written in C. It was created for the sake of
personal edification. I used [RFC 2616](https://tools.ietf.org/html/rfc2616) and
the [Wikipedia page](https://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol) as
references to help guide me in creating this project. I also drew inspiration from
this reddit post: https://www.reddit.com/r/dailyprogrammer/comments/6lti17/20170707_challenge_322_hard_static_http_server/

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

This project is written in C and uses `Cmake` for basic compilation. In
order to compile the project you can either run the build script which will
automatically try to invoke gmake since it's more recent.

    ./build.sh
    cmake . && make

I run `cmake . && gmake` on MacOS because my version of GNU make tends to be
more updated than Apple's provided binary for make. Use whatever version of
`make` you want.

You can also use the build script on a unix-like system if you have `bash`
installed. I haven't tested this project on Windows, but it is compiled
using the clang C compiler, using strict C11. Since CMake is cross-platform,
`cttp` should compile on Windows, but it is not tested and I make no promises.
