# Makefile for cttp main binary
#
# Afnan Enayet	2017
#

# Vars
include_dir=include
include=-I$(include_dir)
src_dir=./src
cc=gcc
flags=-Wall -pedantic -std=c11 -ggdb
prog=cttp
test=cttptest
debug=cttpd
objs=cttp.o

.PHONY: all clean test debug target

all: $(prog) $(test) $(debug)

clean:
	rm -rf *.o *.dYSM
	rm -f cttp cttptest cttpd 

$(prog): $(objs) $(hfiles)
	$(cc) $(cflags) $(objs) $(include) -o $(prog)

cttp.o: $(src_dir)/cttp.c
	$(cc) -c $(src_dir)/cttp.c

