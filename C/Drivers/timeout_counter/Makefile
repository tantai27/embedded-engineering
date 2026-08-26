CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := timeout_counter_test

SRCS    := timeout_counter.c \
           timeout_counter_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

timeout_counter.o: timeout_counter.c timeout_counter.h
	$(CC) $(CFLAGS) -c $< -o $@

timeout_counter_test.o: timeout_counter_test.c timeout_counter.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)