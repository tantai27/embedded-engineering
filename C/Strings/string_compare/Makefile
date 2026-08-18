CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := string_compare_test

SRCS    := string_compare.c \
           string_compare_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

string_compare.o: string_compare.c string_compare.h
	$(CC) $(CFLAGS) -c $< -o $@

string_compare_test.o: string_compare_test.c string_compare.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)