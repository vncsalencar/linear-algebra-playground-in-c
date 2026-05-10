CC = gcc
CFLAGS = -Wall -Wextra
TARGET = main
SOURCES = main.c algebra.c

all: $(TARGET)

$(TARGET): $(SOURCES) algebra.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	DEBUG=1 ./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run debug clean
