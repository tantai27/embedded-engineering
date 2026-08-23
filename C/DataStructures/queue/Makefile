CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := queue_test

SRCS    := queue.c \
           queue_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

queue_test.o: queue_test.c queue.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)