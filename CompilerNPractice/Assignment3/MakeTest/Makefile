TARGET = test
OBJECTS = test.o test1.o test2.o
CC = gcc
CFLAGS = -c

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

test.o: test.c
	$(CC) $(CFLAGS) $<

clean:
	rm $(TARGET) $(OBJECTS)