TARGET = calc
OBJECTS = lex.yy.c parser.tab.c parser.tab.h

$(TARGET): $(OBJECTS)
	gcc -o $@ $^ -lfl

lex.yy.c: scanner.l parser.tab.h
	flex $^

parser.tab.c. parser.tab.h: parser.y
	bison -d $^

clean:
	rm $(OBJECTS) $(TARGET)