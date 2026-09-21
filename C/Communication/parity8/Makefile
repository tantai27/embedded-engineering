CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := parity8_test

SRCS := parity8.c \
        parity8_test.c

OBJS := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

parity8.o: parity8.c parity8.h
	$(CC) $(CFLAGS) -c $< -o $@

parity8_test.o: parity8_test.c parity8.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)