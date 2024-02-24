all: writer

compile=gcc
ifdef CROSS_COMPILE
	compile=aarch64-none-linux-gnu-gcc
endif

writer: writer.c
	$(compile) writer.c -o writer

clean:
	rm -f writer
	rm -f *.o