all: del main clean

CC=gcc -Wall
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

main :
	$(CC) -D LOCALE=fr -D DEBUG ./the_sources/main.c -o main -L./../../lib -lvt100

clean:
	rm -f *.o *~

del:
	rm main