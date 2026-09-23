CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := parity8_test

SRCS := parity8.c \
        parity8_test.c

OBJS := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "LINK    $@"
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@echo "CC      $<"
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -f $(OBJS) $(TARGET)
	@echo "CLEAN   build artifacts"