CC=gcc
CFLAGS=-Wall -Wextra -O3
EXAMPLES=./examples/
HELLOWORLD=hello-world/
HELLOWORLDEXSERVER=$(BUILD)/hello-world-server
HELLOWORLDSERVERC=$(EXAMPLES)$(HELLOWORLD)hello-world-server.c
HELLOWORLDEXCLIENT=$(BUILD)/hello-world-client
HELLOWORLDCLIENTC=$(EXAMPLES)$(HELLOWORLD)hello-world-client.c
OSCORE=./libs
MUTEXOUTDIR=mutex
MUTEXOUT=$(BUILD)/mutex.o
BUILD=./build
MUTEXIN=mutex/mutex.c
MUTEXH=mutex/mutex.h

.PHONY: all examples clean_examples libs clean

all: libs examples

examples: $(HELLOWORLDEXSERVER) $(HELLOWORLDEXCLIENT)

$(HELLOWORLDEXSERVER): $(HELLOWORLDSERVERC) $(MUTEXOUT)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< -I$(BUILD)/$(MUTEXOUTDIR)/ $(MUTEXOUT)

$(HELLOWORLDEXCLIENT): $(HELLOWORLDCLIENTC) $(MUTEXOUT)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -o $@ $< -I$(BUILD)/$(MUTEXOUTDIR)/ $(MUTEXOUT)

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

