CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := watchdog_simulator_test

SRCS := watchdog_simulator.c \
        watchdog_simulator_test.c

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