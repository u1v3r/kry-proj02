# Makefile pre KRY-proj02

CC = gcc
PNAME = kry
CFLAGS = -Wall -ansi -pedantic -lgmp -pg -g

objects = gen.o enc_dec.o global_fcs.o


rebuild: clean all

all: $(PNAME).c $(objects)
	$(CC) $(CFLAGS) -o $(PNAME) $(PNAME).c $(objects)

enc_dec.o: enc_dec.h enc_dec.c
	$(CC) $(CFLAGS) -c -o enc_dec.o enc_dec.c 

global_fcs.o: global_fcs.h global_fcs.c
	$(CC) $(CFLAGS) -c -o global_fcs.o global_fcs.c 
	
gen.o: gen.h gen.c
	$(CC) $(CFLAGS) -c -o gen.o gen.c

clean: $(PNAME).c
	rm -f $(PNAME) *.o *.out *.sum