CC=g++
CFLAGS= -c -Wall
LDFLAGS= $(shell pkg-config --libs opencv)
SOURCES=video_test.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLES=video

all: $(SOURCES) $(EXECUTABLES)

#video: $(OBJECTS) 
	#$(CC) $(OBJECTS) $(LDFLAGS) -o $@

#pong: $(OBJECTS) 
	#$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
