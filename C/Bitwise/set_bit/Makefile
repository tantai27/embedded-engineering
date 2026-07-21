CC      := gcc

CFLAGS  := -std=c11
CFLAGS  += -Wall
CFLAGS  += -Wextra
CFLAGS  += -Wpedantic
CFLAGS  += -Wconversion
CFLAGS  += -Wsign-conversion
CFLAGS  += -g

TARGET  := set_bit_test

SRCS    := set_bit.c \
           set_bit_test.c

OBJS    := $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

%.o: %.c set_bit.h
	$(CC) $(CFLAGS) -c $<

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)