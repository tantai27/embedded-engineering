CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := string_reverse_test

SRCS    := string_reverse.c \
           string_reverse_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

string_reverse.o: string_reverse.c string_reverse.h
	$(CC) $(CFLAGS) -c $< -o $@

string_reverse_test.o: string_reverse_test.c string_reverse.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)