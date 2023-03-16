CC 			= g++
CFLAGS 		= -Wall -O2 -g -I./src
LIBS 		= -lm
BIN 		= ./bin/main
BUILD		= ./build
SRCS		= $(shell find . -name '*.cc')
OBJECTS		= $(patsubst %.cc, $(BUILD)/%.o, $(SRCS))

all: $(BIN)

$(BUILD)/%.o: %.cc $(BUILD)
	@mkdir -p '$(@D)'
	$(info CC $<)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LIBS)

$(BIN): $(OBJECTS) $(BUILD)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LIBS)

clean:
	rm -rf ./bin/* ./build/*
