all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

main :
	$(CC) -D LOCALE=fr -D DEBUG ./the_sources/main.c -o main -L./../../lib -lvt100
	export LD_LIBRARY_PATH=.

clean:
	rm -f *.o *~
