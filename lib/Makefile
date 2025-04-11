
src = $(wildcard *.c)
obj = $(src:.c=.o)
lib = libpdf.a

CC = gcc
CFLAGS = -std=c17 -O2 -Wall -Wextra
ARFLAGS = rcs

$(lib): $(obj)
	$(AR) $(ARFLAGS) $@ $^

.PHONY: clean
clean:
	rm $(obj) $(lib)
