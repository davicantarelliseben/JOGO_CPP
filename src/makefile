RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS := $(shell pkg-config --libs raylib 2>/dev/null || echo "-lraylib -lGL -lm -lpthread -ldl -lrt -lX11")
CXXFLAGS ?= -std=c++17 -Wall -Wextra -pedantic
SOURCES := main.cpp RaylibGame.cpp Character.cpp Player.cpp Inventory.cpp Item.cpp Enemy.cpp Battle.cpp Map.cpp Tiles.cpp Event.cpp
HEADERS := $(wildcard include/*.h)
TARGET := jogo

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) $(SOURCES) -Iinclude $(RAYLIB_LIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: commit

commit:
	@echo Digite a mensagem do commit:
	@set /p msg="" && cmd /v:on /c "git add . && git commit -m "!msg!" && git push origin main"

.PHONY: all run