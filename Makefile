CC=gcc
CFLAGS=-pedantic -Wall -lncurses -Wformat=0
CFLAGS+=-I/usr/include -L/usr/lib64 -lbsd

ifeq ($(OS), LINUX)
	CFLAGS+=-I/usr/include -L/usr/lib64 -lbsd
	echo "HEI"
	echo "HEI"
	echo "HEI"
	echo "HEI"
	echo "HEI"
endif

all:
	${CC} ${CFLAGS} -g -o soko sokoban.c 
