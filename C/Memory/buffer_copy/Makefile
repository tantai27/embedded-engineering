CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := buffer_copy_test

SRCS    := buffer_copy.c \
           buffer_copy_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

buffer_copy.o: buffer_copy.c buffer_copy.h
	$(CC) $(CFLAGS) -c $< -o $@

buffer_copy_test.o: buffer_copy_test.c buffer_copy.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)