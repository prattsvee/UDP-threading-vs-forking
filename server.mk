# Compiler
CC = gcc
# Compiler flags
CFLAGS = -Wall -Wextra -std=c99
# Source files
SERVER_SRC = server.c calculator.c
# Header files
SERVER_HEADERS = server_config.h calculator.h
# Object files
SERVER_OBJ = $(SERVER_SRC:.c=.o)
# Output executable
SERVER_EXEC = server

# Build server
$(SERVER_EXEC): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile server source files
%.o: %.c $(SERVER_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(SERVER_EXEC) $(SERVER_OBJ)
