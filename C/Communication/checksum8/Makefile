CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -Wpedantic
TARGET  := checksum8_test

SRCS    := checksum8.c \
           checksum8_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

checksum8.o: checksum8.c checksum8.h
	$(CC) $(CFLAGS) -c $< -o $@

checksum8_test.o: checksum8_test.c checksum8.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)