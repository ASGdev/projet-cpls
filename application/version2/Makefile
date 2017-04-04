all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

# Executable
main : main.o tap.o
	$(CC) -o $@ $^

main.o:
	$(CC) $(INCLUDE) -D LOCALE=en -c $(SRC_DIR)/testing/main.c

tap.o:
	$(CC) $(INCLUDE) -c $(SRC_DIR)/testing/tap.c

clean:
	rm -f *.o *~ 

