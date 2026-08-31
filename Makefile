CC = clang
TARGET = kvstore
CFLAGS = -Wall -Wextra -g

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

clean :
	rm -f $(TARGET) main.o