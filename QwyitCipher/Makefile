CC=gcc
CFLAGS=-I.
DEPS = ../DefineQ.h IO.h PrimitiveQ.h CipherQ.h
OBJ = IO.o PrimitiveQ.o CipherQ.o main.o 

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -g -o $@ $^ $(CFLAGS)
	rm *.o
.PHONY: clean

clean:
	rm -f *.o qwyit

