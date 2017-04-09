all: del main clean

CC=gcc -Wall
SRC_DIR=the_sources
INCLUDE=-I./the_headers

OPTIM=-O2

# Executable
main:
	# $(CC) $(INCLUDE) -L/media/bastien/DATA/polytech/csystem/projet/clone3/projet-cpls/lib/ -lvt100 $(SRC_DIR)/main.c -o $@
	$(CC) $(INCLUDE) ./the_sources/*.c -o main -L./../../lib -lvt100
	# export LD_LIBRARY_PATH=.
	# main.o:
	# 	$(CC) $(INCLUDE) -c $(SRC_DIR)/main.c

clean:
	rm -f *.o *~

del:
	rm main