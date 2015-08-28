# the compiler: gcc for C program, define as g++ for C++
CXX = g++
ARGS=weird.js
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
LOADLIBES = -lcurl -lv8 -lpthread

# the build target executable:
TARGET = jsEngine

#all: $(TARGET)

run:
	$(CXX) $(TARGET).cpp $(LOADLIBES) -o $(TARGET)
	
	./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET)
