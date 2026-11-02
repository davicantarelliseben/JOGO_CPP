CPP      = g++
CPPFLAGS = -Werror -Wall -Iinclude
TARGET   = jogo

all: $(TARGET)

$(TARGET): src/*.cpp
	$(CPP) $(CPPFLAGS) src/*.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean