CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := linear_search_test

SRCS    := linear_search.c \
           linear_search_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

linear_search.o: linear_search.c linear_search.h
	$(CC) $(CFLAGS) -c $< -o $@

linear_search_test.o: linear_search_test.c linear_search.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)