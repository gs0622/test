.PHONY: all clean

all: server.c client.c
	gcc -g -Wall server.c -o server -lpthread
	gcc -g -Wall client.c -o client -lpthread

clean:
	rm -f server client
