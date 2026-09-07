CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := bit_rotate_test

SRCS := bit_rotate.c \
        bit_rotate_test.c

OBJS := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)