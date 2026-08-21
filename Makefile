cc = gcc

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
CPPFLAGS = -Iinclude

SRC = \
      src/main.c \
      src/commands/pwd.c \
      src/commands/cat.c \
      src/commands/echo.c \
      src/commands/touch.c \
      src/commands/mkdir.c \
      src/commands/rm.c \
      src/commands/ls.c \
      src/commands/cp.c \
      src/lib/io.c 

OBJ = $(SRC:.c=.o)

linix: $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) linix

.PHONY: clean
