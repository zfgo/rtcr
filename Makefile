CC 			= g++
CFLAGS 		= -Wall -O2 -g -I./src
LIBS 		= -lm
BIN 		= ./bin/main
BUILD		= ./build
SRCS		= $(shell find . -name '*.c')
OBJECTS		= $(patsubst %.c, $(BUILD)/%.o, $(SRCS))

all: $(BIN)

$(BUILD)/%.o: %.c $(BUILD)
	@mkdir -p '$(@D)'
	$(info CC $<)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BIN): $(OBJECTS) $(BUILD)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -rf ./bin/* ./build/*
