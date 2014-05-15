CXX = g++
CFLAGS =
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SRCS = sprite.cpp
BIN = move_sprite

all: $(SRCS)
	$(CXX) $(SRCS) $(LFLAGS) -o $(BIN)

.PHONY: all clean

clean:
	-rm -f $(BIN)
