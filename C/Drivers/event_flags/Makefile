CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := event_flags_test

SRCS := event_flags.c \
        event_flags_test.c

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