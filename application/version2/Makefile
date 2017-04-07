all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

# Executable
main :
	$(CC) $(INCLUDE) -D LOCALE=en $(SRC_DIR)/testing/main.c -o $@ -L./../../lib -lvt100

clean:
	rm -f *.o *~ 

