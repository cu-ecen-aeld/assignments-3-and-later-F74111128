<<<<<<< HEAD
all: writer

CC = $(CROSS_COMPILE)gcc

writer: writer.c
	$(CC) writer.c -o writer
=======
CFLAGS=-I.
DEPS = ""
OBJ = writer.o 

ifdef CROSS_COMPILE
	ifeq ($(CROSS_COMPILE),aarch64-none-linux-gnu-)
		CC=${CROSS_COMPILE}gcc
	else
		CC=gcc
	endif
else
	CC=gcc
endif

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

writer: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
>>>>>>> 36427d2c9f66ba46565b46f0221c85349785c4de

clean:
	rm -f writer *.o
