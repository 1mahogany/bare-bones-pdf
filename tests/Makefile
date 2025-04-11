
src = $(wildcard *.c)
obj = $(src:.c=.o)
bin = fwf

CC = gcc
CFLAGS = -std=c17 -O2 -Wall -Wextra -I../lib
LDFLAGS = -L../lib -lpdf -lz

$(bin): $(obj)
	$(CC) $^ -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	rm $(bin) $(obj)
