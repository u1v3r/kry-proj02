# Makefile pre KRY-proj02

CC = gcc
PNAME = kry
CFLAGS = -Wall -march=core2 -pedantic -lgmp -lm -ldl -lz -lpthread -I$(MSIEVE_SUBDIR)/include -pg -g 
MSIEVE_SUBDIR = msieve

objects = gen.o enc_dec.o global_fcs.o crack.o

rebuild:	clean msieve_build all

all: $(PNAME).c $(objects)
	$(CC) $(CFLAGS) -o $(PNAME) $(PNAME).c $(objects) $(MSIEVE_SUBDIR)/libmsieve.a

msieve_build:	
	make -C $(MSIEVE_SUBDIR)

enc_dec.o: enc_dec.h enc_dec.c
	$(CC) $(CFLAGS) -c -o enc_dec.o enc_dec.c 

global_fcs.o: global_fcs.h global_fcs.c
	$(CC) $(CFLAGS) -c -o global_fcs.o global_fcs.c 
	
crack.o: crack.h crack.c
	$(CC) $(CFLAGS) -c -o crack.o crack.c
	
gen.o: gen.h gen.c
	$(CC) $(CFLAGS) -c -o gen.o gen.c

clean: $(PNAME).c
	rm -f $(PNAME) *.o *.out *.sum *.dat
	#make clean -C $(MSIEVE_SUBDIR)