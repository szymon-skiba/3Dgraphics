CC = g++
CFLAGS = -Wall
LIBS = -lGL -lGLU -lglfw -lm

SOURCES = camera3D.cpp cube.cpp transformations.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = camera3D

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

