# Makefile

CC=g++
CFLAGS=-Wall
LIBS=-lm -lglut -lGL -lGLU -lglfw -lGLEW -lpthread
SOURCES=sphere.cpp material.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE=sphere

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: clean
