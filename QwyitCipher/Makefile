CC=gcc
CFLAGS=-I.
DEPS = PrimativeQ.h CipherQ.h IO.h
OBJ = main.o PrimativeQ.o IO.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm *.o
.PHONY: clean

clean:
	rm -f *.o qwyit

