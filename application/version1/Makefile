all: main clean

CC=gcc
SRC_DIR=the_sources
INCLUDE=-Ithe_headers

OPTIM=-O2

# Executable
main :
	# $(CC) $(INCLUDE) -L/media/bastien/DATA/polytech/csystem/projet/clone3/projet-cpls/lib/ -lvt100 $(SRC_DIR)/main.c -o $@ 

	$(CC) ./the_sources/main.c -o main -L./../../lib -lvt100

# main.o:
# 	$(CC) $(INCLUDE) -c $(SRC_DIR)/main.c
	
clean:
	rm -f *.o *~