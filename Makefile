.PHONY: all clean cleanall

CC=clang
SRC=$(wildcard *.c)
OBJS=$(SRC:.c=.o)
CFLAGS=-Wall -ggdb          # if necessary add new options
SYMBOLS=-DUTF8_SYMBOLS2     # alternatives are: -DUTF8_SYMBOLS1 or -DASCII_SYMBOLS

.PHONY: all clean cleanall test

all: simulation

simulation: $(OBJS)
	gcc $(SYMBOLS) $(CFLAGS) $(OBJS) -o simulation

clean:
	@- rm $(OBJS)

cleanall: clean
	@- rm simulation

test: all
	@- echo -n "Testing"; \
	   for i in {1..10}; \
	   do \
	      echo -n "."; \
		  echo "" | ./simulation -f 2 -k 1 -n 10 > /dev/null; \
	   done; \
	   printf "\nDone!\n"
