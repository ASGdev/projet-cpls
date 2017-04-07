all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

main :
	$(CC) ./the_sources/testing/main.c -o main -L./../../lib -lvt100

clean:
	rm -f *.o *~