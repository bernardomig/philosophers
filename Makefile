.PHONY: all clean cleanall

CC=clang
SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)
CFLAGS=-Wall -ggdb          # if necessary add new options
SYMBOLS=-DUTF8_SYMBOLS2     # alternatives are: -DUTF8_SYMBOLS1 or -DASCII_SYMBOLS

all: simulation

simulation: $(OBJS)
	gcc $(SYMBOLS) $(CFLAGS) $(OBJS) -o simulation

clean:
	@- rm $(OBJS)

cleanall: clean
	@- rm simulation

