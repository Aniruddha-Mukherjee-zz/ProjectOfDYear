# the compiler: gcc for C program, define as g++ for C++
CXX = g++
ARGS=weird.js

LOCAL_SHARED_LIBRARIES := v8

LOADLIBES = -lcurl  -lpthread

# the build target executable:
TARGET = jsEngine
LOCAL_CPP_INCLUDES= $(LOCAL_PATH)/include/

#all: $(TARGET)

run:
	$(CXX) $(TARGET).cpp  -l $(LOCAL_SHARED_LIBRARIES) -I $(LOCAL_CPP_INCLUDES)  $(LOADLIBES) -o $(TARGET)

	./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET)
