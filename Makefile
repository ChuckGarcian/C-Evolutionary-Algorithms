# Compiler and flags
CC = gcc
CFLAGS = -Wall -I/usr/local/include -I./include/ -I./src
LFLAGS = -L/usr/local/lib -lgsl -lgslcblas -lm -ltensor

# Directories
BIN = bin
SRC = src
DIRS = $(SRC)
DIRPATHS = $(foreach DIR, $(DIRS), $(shell find $(DIR) -type d))

# Include paths
IFLAGS = $(DIRPATHS:%=-I%)

# Set up search path for source files
VPATH = $(DIRPATHS)

# Find all .c files
SRC_FILES = $(shell find $(SRC) -name '*.c')

# Default target
all: $(BIN)/app.x

# Compile the main application
$(BIN)/app.x: $(SRC_FILES)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $@

# Run a specific file
run_%: $(BIN)/%
	@$<

# Build a specific file
build_%: %.c $(SRC_FILES)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $(BIN)/$*

# Debug a specific file
debug_%: CFLAGS += -g -O0
debug_%: %.c $(SRC_FILES)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $(BIN)/$*

# Plot (kept from your original Makefile)
graph:
	python3 src/plot.py

# Clean up
clean:
	rm -rf $(BIN)

.PHONY: all clean graph