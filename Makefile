OBJS = main.cpp $(wildcard src/*.cpp)

OBJ_NAME = bin/chip8

INCLUDE_PATHS = -I.\src -I..\SDL2\include\SDL2

LIBRARY_PATHS = -L..\SDL2\lib

COMPILER_FLAGS = -w 
#These flags are left out for debug builds
#-Wl,-subsystem,windows

LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
#	This flag is left out for debug builds
#-mwindows
#SDL2 flags left out until graphics implementation
#-lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf

STD = -std=c++14

all: $(OBJS)
	g++ $(OBJS) $(STD) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) $(COMPILER_FLAGS) -o $(OBJ_NAME)
