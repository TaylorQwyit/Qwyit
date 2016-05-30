CC=gcc
CFLAGS=-I.
DEPS = ../QwyitCipher/PrimativeQ.h ../QwyitCipher/CipherQ.h ../QwyitCipher/IO.h CompressTree.h
OBJ = main.o CompressTree.o ../QwyitCipher/PrimativeQ.o ../QwyitCipher/CipherQ.o ../QwyitCipher/IO.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm *.o
.PHONY: clean

clean:
	rm -f *.o qwyit

