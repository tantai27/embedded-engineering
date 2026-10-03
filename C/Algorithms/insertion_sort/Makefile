CC := gcc

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic

TARGET := insertion_sort_test

SRCS := insertion_sort.c \
        insertion_sort_test.c

OBJS := $(SRCS:.c=.o)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "LINK    $@"
	@$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@echo "CC      $<"
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -f $(OBJS) $(TARGET)
	@echo "CLEAN   build artifacts"