TARGET = pascal_like
MAIN = main.c
OBJECTS = pascal_like.tab.c lex.yy.c
LINK_FILES = pascal_like.tab.h

$(TARGET): $(MAIN) $(OBJECTS)
	gcc -o $@ $^ -lfl -DYYDEBUG

lex.yy.c: pascal_like.l
	flex $^

pascal_like.tab.h pascal_like.tab.c: pascal_like.y
	bison -d $^

clean:
	rm $(TARGET) $(OBJECTS) $(LINK_FILES)