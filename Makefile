CC=g++
CFLAGS=-c -Wall 
LDFLAGS=
SOURCES=main.cpp \
        classElf.cpp \
        classTribe.cpp \

SOURCES+= \

OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=play

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean: 
	find . -name "*.o"  | xargs rm -f
	rm $(EXECUTABLE)
