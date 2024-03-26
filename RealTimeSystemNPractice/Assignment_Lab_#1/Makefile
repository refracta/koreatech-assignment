TARGET=test
OBJECT=test.o test1.o test2.o
CC=gcc
CFLAGS=-c

all: $(TARGET)

$(TARGET): $(OBJECT)
	gcc -o $(TARGET) $(OBJECT)

c.o:
	gcc $(CFLAGS) $<

test2.o: test2.c
		gcc $(CFLAGS) -I/usr/lib/include -Im -L/usr/lib -DDEBUG $<

clean:
	rm $(TARGET) $(OBJECT)
