CC := gcc
CFLAGS := -Wall -O3 -I./include
LINKER := gcc
LDFLAGS := -lgsl -lgslcblas -lm -ltensor
SRC := src
BIN := bin
DRIVER_SRCS := $(shell find $(SRC) -name '*_driver.c')
HELPER_SRCS := $(shell find $(SRC) -name "*.c" -not -name "*_driver.c")

# Convert source file paths to object file paths in the BIN directory
DRIVER_OBJS := $(patsubst $(SRC)/%.c,$(BIN)/%.o,$(DRIVER_SRCS))
HELPER_OBJS := $(patsubst $(SRC)/%.c,$(BIN)/%.o,$(HELPER_SRCS))


# Ensure the BIN directory exists
$(BIN):
	mkdir -p $(BIN)

# Pattern rule to create object files in the BIN directory, maintaining subdirectory structure
$(BIN)/%.o: $(SRC)/%.c | $(BIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to find and compile the driver source file
compile_%: $(BIN)/%_driver.o $(HELPER_OBJS)
	$(LINKER) $(BIN)/$*_driver.o $(HELPER_OBJS) -o $(BIN)/driver_gemm.x $(LDFLAGS)

$(BIN)/%_driver.o: 
	@src_file=$(shell find $(SRC) -name "$*_driver.c"); \
	$(CC) $(CFLAGS) -c $$src_file -o $@

show:
	echo $(HELPER_OBJS)

debug_%: CFLAGS = -DDEBUG -g -Wall -O0 -I./include/
debug_%: $(BIN)/%_driver.o $(HELPER_OBJS)
	$(LINKER) $(BIN)/$*_driver.o $(HELPER_OBJS) -o $(BIN)/driver_gemm.x $(LDFLAGS)

run_%: $(BIN)/%_driver.o $(HELPER_OBJS)
	$(LINKER) $(BIN)/$*_driver.o $(HELPER_OBJS) -o $(BIN)/driver_gemm.x $(LDFLAGS)
	$(BIN)/driver_gemm.x  

run:
	$(BIN)/driver_gemm.x  

clean:
	rm -rf $(BIN)