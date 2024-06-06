CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lGL -lGLU -lglut -lGLEW

SRCS = src/main.cpp src/utils.cpp lib/tiny_obj_loader.cpp
OBJS = $(SRCS:.cpp=.o)

TARGET = model_viewer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
