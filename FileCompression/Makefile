CC=gcc
CFLAGS=-I.
DEPS = ../DefineQ.h ../QwyitCipher/IO.h ../QwyitCipher/PrimitiveQ.h ../QwyitCipher/CipherQ.h CompressTree.h
#../QwyitCipher/PrimativeQ.h ../QwyitCipher/CipherQ.h ../QwyitCipher/IO.h ../DefineQ.h CompressTree.h
OBJ = ../QwyitCipher/IO.o ../QwyitCipher/PrimitiveQ.o ../QwyitCipher/CipherQ.o CompressTree.o main.o
#main.o CompressTree.o ../QwyitCipher/PrimativeQ.o ../QwyitCipher/CipherQ.o ../QwyitCipher/IO.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm *.o ../QwyitCipher/*.o

.PHONY: clean

clean:
	rm -f *.o ../QwyitCipher/*.o qwyit

