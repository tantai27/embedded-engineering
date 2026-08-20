CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := string_copy_test

SRCS    := string_copy.c \
           string_copy_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

string_copy.o: string_copy.c string_copy.h
	$(CC) $(CFLAGS) -c $< -o $@

string_copy_test.o: string_copy_test.c string_copy.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)