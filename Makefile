# Directory Settings
BIN := bin
SRC_DIR := src
USER := chuckg
GSL_SRC := home/$(USER)/gsl

# Compilation Settings
IFLAGS := -I/usr/local/include
LFLAGS := -L/usr/local/lib -lgsl -lgslcblas -lm -ltensor
CFLAGS := -Wall 

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN)/%.o,$(SRCS))

HELPER_SRCS := $(shell grep -L "int main" $(SRC_DIR)/*.c)
HELPER_OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN)/%.o,$(HELPER_SRCS))

.PHONY: all build clean run_%

default: run

build: $(BIN)/app.x

debug: CFLAGS += -g
debug: LFLAGS += -g
debug: build

$(BIN)/app.x: $(OBJS)
	gcc $^ $(OPT) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@

$(BIN)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BIN)
	gcc $(OPT) $(CFLAGS) $(IFLAGS) -c $< -o $@

run: build
	$(BIN)/app.x

run_%: $(SRC_DIR)/%.c $(HELPER_OBJS)
	mkdir -p $(BIN)
	gcc $(OPT) $(CFLAGS) $(IFLAGS) $^ $(LFLAGS) -o $(BIN)/$*.x
	$(BIN)/$*.x
	
clean:
	$(RM) -rf $(BIN) src/*.txt src/plot.png