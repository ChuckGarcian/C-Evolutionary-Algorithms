# Directory Settings
BIN := bin
SRC_DIR := ./
USER := chuckg
GSL_SRC := home/$(USER)/gsl

# Compiliation Settings
IFLAGS := -I/usr/local/include
LFLAGS := -L/usr/local/lib -lgsl -lgslcblas -lm  -ltensor
CFLAGS := -Wall 

# SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := main.o
OBJS := $(patsubst $(SRC_DIR)/%.c,%.o,$(SRCS))

.PHONY: all build clean 

default: run

build: $(BIN)/app.x

$(BIN)/app.x: $(OBJS)
	mkdir -p $(BIN)
	gcc $^ $(OPT) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@

%.o: $(SRC_DIR)/%.c
	gcc $(OPT) $(CFLAGS) $(IFLAGS) -c $< -o $@ 
	
run: build
	$(BIN)/app.x

clean:
	$(RM) -rf $(BIN) $(OBJS)