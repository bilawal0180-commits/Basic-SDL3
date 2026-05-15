CXX = g++
CXXFLAGS = -std=c++23 -Iinclude
LDFLAGS = -Llib -lSDL3

TARGET = main
SRCS = main.cpp include/Game/gameLoop.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).exe