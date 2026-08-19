cc = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

SRC = \
      src/main.c \
      src/commands/pwd.c

OBJ = $(SRC:.c=.o)

linix: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) linix

.PHONY: clean
