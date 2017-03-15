all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

# Executable
main : main.o
	$(CC) -o $@ $^
	cp $@ bin/

main.o: main.c
    $(CC) $(INCLUDE)  -c  $<
	
clean:
	rm -f *.o *~ 

