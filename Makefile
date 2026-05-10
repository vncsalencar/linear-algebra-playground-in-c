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

%: %.c algebra.c algebra.h
	$(CC) $(CFLAGS) $< algebra.c -o $@

run-%: %
	./$*

debug-%: %
	DEBUG=1 ./$*

.PHONY: all run debug clean
