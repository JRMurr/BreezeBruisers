CC=g++
CFLAGS=-I /usr/include/SDL2
DEVFLAGS=-Wunused -g
TARGET=build/main
# point to all the source paths
vpath %.cpp source:source/characters:source/states:source/utilities

BUILDDIRS=build

RESOURCES=build/resources

# OBJS=$(find source -type f -name "*.cpp" | awk 'match($NF, /(\w+).cpp/, a) {print a[1]}' | xargs -I % echo -n "%.o ")
OBJS=$(addprefix build/,Character.o Goal.o Animation.o StateManager.o HiddenState.o MainMenu.o MainState.o Entity.o Button.o Timer.o SpriteSheet.o main.o Disk.o Player.o Wall.o STexture.o)


all: $(TARGET)

build/main: $(OBJS) $(RESOURCES)
	$(CC) -lm -lSDL2 -lSDL2_image -lSDL2_mixer build/*.o -o build/main

# generic cpp build rule
build/%.o: %.cpp | $(BUILDDIRS)
	$(CC) -c $(CFLAGS) $(DEVFLAGS) $< -o build/$(@F)

main.o: source/main.cpp include/states/StateManager.h include/states/MainState.h include/states/MainMenu.h | $(BUILDDIRS)
	$(CC) -c $(CFLAGS) $(DEVFLAGS) $< -o build/$@

$(RESOURCES): resources | $(BUILDDIRS)
	mkdir -p build/resources; cp $</* $@

$(BUILDDIRS):
	mkdir $@

clean:
	rm -rf ./build/*
