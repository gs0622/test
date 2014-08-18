.PHONY: all clean

all: foo.h
	gcc -Wall -Werror -fpic foo.c -shared -o libfoo.so
	gcc -Wall main.c -lfoo -L. -Wl,-rpath=.

clean:
	rm -f libfoo.so a.out
