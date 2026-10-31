CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude
SRCS     = $(wildcard src/*.cpp)
OBJS     = $(SRCS:src/%.cpp=src/%.o)
TARGET   = jogo.exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q /S src\*.o $(TARGET) 2>nul || rm -f src/*.o $(TARGET)

.PHONY: all clean