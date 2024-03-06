all: server

CC = $(CROSS_COMPILE)gcc

server: server.c
	$(CC) -o aesdsocket server.c

clean:
	rm -f aesdsocket
