CC=gcc
CFLAGS=-I.
DEPS = QwyitCipher.h Util_IO.h
OBJ = main.o #QwyitCipher.o Util_IO.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
qwyit: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)
	rm *.o
.PHONY: clean

clean:
	rm -f *.o qwyit

