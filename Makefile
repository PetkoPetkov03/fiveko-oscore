CC=gcc
CFLAGS=-Wall -Wextra -O3 -g
EXAMPLES=./examples
OSCORE=./libs
BUILD=build
INC=./include

.PHONY: all examples clean_examples libs clean

SRCEX := $(shell find $(EXAMPLES) -name '*.c')
OBJEX := $(patsubst $(EXAMPLES)/%.c, $(EXAMPLES)/%.a, $(SRCEX))

examples: $(OBJEX)

$(EXAMPLES)/%.a: $(EXAMPLES)/%.c
	$(CC) $(CFLAGS) -I$(INC) $(BUILD)/**/* $< -o $@ 

SRCH := $(shell find $(OSCORE) -name '*.h')
OBJH := $(patsubst $(OSCORE)/%.h, $(INC)/%.h, $(SRCH))

SRCC := $(shell find $(OSCORE) -name '*.c')
OBJC := $(patsubst $(OSCORE)/%.c, $(BUILD)/%.o, $(SRCC))

libs: $(OBJC) $(OBJH)

$(INC)/%.h: $(OSCORE)/%.h
	@mkdir -p $(dir $@)
	cp $< $@

$(BUILD)/%.o: $(OSCORE)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(INC)
	rm -rf $(BUILD)

