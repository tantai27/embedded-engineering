CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := parentheses_validator_test

SRCS    := parentheses_validator.c \
           parentheses_validator_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

parentheses_validator.o: parentheses_validator.c parentheses_validator.h
	$(CC) $(CFLAGS) -c $< -o $@

parentheses_validator_test.o: parentheses_validator_test.c parentheses_validator.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)