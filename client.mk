# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -std=c99
# Source files
CLIENT_SRC = client.c
# Header files
CLIENT_HEADERS = client_config.h
# Object files
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
# Output executable
CLIENT_EXEC = client

# Build client
$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile client source files
%.o: %.c $(CLIENT_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(CLIENT_EXEC) $(CLIENT_OBJ)
