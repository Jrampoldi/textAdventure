CC := g++
OPTCFLAGS := -Wall -Werror
CFLAGS := -I ./include
OBJECTS := main.o world.o player.o npc.o item.o algorithms.o
SOURCES := $(shell ls lib/*.cpp main.cpp) 
EXEC := adventure_game
RM := rm -f

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ 

main.o: $(SOURCES)
	$(CC) -c $(SOURCES) $(CFLAGS)

%.o: lib/%.cpp include/%.h
	$(CC) -c lib/%.cpp include/%.h

.PHONY: clean

clean:
	$(RM) $(EXEC) $(OBJECTS)
