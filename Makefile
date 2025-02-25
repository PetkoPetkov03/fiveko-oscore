CC=gcc
CFLAGS=-Wall -Wextra -O3
EXAMPLES=./examples/
OSCORE=./libs
BUILD=./build

.PHONY: all examples clean_examples libs clean

SRC := $(shell find $(OSCORE) -name '*.c')
OBJ := $(patsubst $(OSCORE)/%.c, $(BUILD)/%.o, $(SRC))

libs: $(OBJ)

$(BUILD)/%.o: $(OSCORE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(MUTEXOUT): $(MUTEXIN) $(MUTEXH)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

clean_examples:
	rm -f $(HELLOWORLDEXSERVER) $(HELLOWORLDEXCLIENT)

clean:
	rm -rf $(BUILD)

