# the compiler: gcc for C program, define as g++ for C++
CXX = g++
ARGS=weird.js

LOCAL_SHARED_LIBRARIES := v8 curl

LOADLIBES =  -lpthread

# the build target executable:
TARGET = jsEngine
v8_INCLUDES= $(LOCAL_PATH)/include/v8
curl_INCLUDES=$(LOCAL_PATH)/include/curl

#all: $(TARGET)

run:
	$(CXX) $(TARGET).cpp  -lv8 -I $(v8_INCLUDES) -lcurl -I $(curl_INCLUDES)  $(LOADLIBES) -o $(TARGET)

	./$(TARGET) $(ARGS)

clean:
	$(RM) $(TARGET)
