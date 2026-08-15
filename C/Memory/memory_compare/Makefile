CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := memory_compare_test

SRCS    := memory_compare.c \
           memory_compare_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

memory_compare.o: memory_compare.c memory_compare.h
	$(CC) $(CFLAGS) -c $< -o $@

memory_compare_test.o: memory_compare_test.c memory_compare.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)