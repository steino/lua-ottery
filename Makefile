LUACPATH = /usr/lib/lua/5.1

SRCNAME = src/lua-ottery.c
LIBNAME = ottery.so

CFLAGS = $(shell pkg-config lua --cflags || pkg-config lua5.1 --cflags)-Os -fpic
LFLAGS = -shared -L/usr/lib -lottery

CC = gcc

all: $(LIBNAME)

$(LIBNAME):
	$(CC) -O2 -o $(LIBNAME) $(SRCNAME) $(CFLAGS) $(LFLAGS) -Wall

install: $(LIBNAME)
	cp $(LIBNAME) $(LUACPATH)

uninstall:
	rm $(LUACPATH)/$(LIBNAME)

clean:
	rm -f $(LIBNAME)

test: $(LIBNAME)
	lua test/test.lua

.PHONY: all test clean
