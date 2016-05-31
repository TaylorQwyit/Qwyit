CC=gcc
CFLAGS=-I.
DEPS = ../DefineQ.h IO.h PrimativeQ.h #CipherQ.h
OBJ = IO.o PrimativeQ.o main.o #CipherQ.o main.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm *.o
.PHONY: clean

clean:
	rm -f *.o qwyit

