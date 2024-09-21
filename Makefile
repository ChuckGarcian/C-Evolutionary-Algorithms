# Directory Settings
BIN := bin
SRC_DIR := src
USER := chuckg
GSL_SRC := home/$(USER)/gsl

# Compilation Settings
IFLAGS := -I/usr/local/include
LFLAGS := -L/usr/local/lib -lgsl -lgslcblas -lm -ltensor
CFLAGS := -Wall 

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BIN)/%.o,$(SRCS))

.PHONY: all build clean 

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

clean:
	$(RM) -rf $(BIN)