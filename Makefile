cc = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

SRC := $(wildcard src/commands/*.c) \
       $(wildcard src/lib/*.c) \
       src/main.c

OBJ := $(SRC:.c=.o)

linix: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) linix

.PHONY: clean
