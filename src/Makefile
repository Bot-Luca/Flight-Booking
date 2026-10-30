CC ?= gcc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra
TARGET := flight

.PHONY: all run clean

all: $(TARGET)

$(TARGET): code.c header.h
	$(CC) $(CFLAGS) -o $(TARGET) code.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
