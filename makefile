CXX = g++
SOURCES =  XMLHttpRequest.cpp jsEngine.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ARGS=weird.js
LDFLAGS = -lcurl -lv8 -lpthread
CFLAGS = -g -Wall
EXECUTABLE = jsEngine

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): xmlhttp  jsengine
	
xmlhttp:
	$(CC) -c $(CFLAGS)   XMLHttpRequest.cpp
jsengine:
	$(CC) -c $(CFLAGS)  jsEngine.cpp
