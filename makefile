CPP = g++.exe
LIBS = -L"Dependencies/SDL2/lib"
INCS = -I"Dependencies/SDL2/include" -I"src"
FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf 
BIN = bin/NatalIDE.exe
WINDOWS = -mwindows #Add to get rid of command console
RELEASE = -Wall -O2 # Add for release version... Should run faster than normal... Should.

BUILDFLAGS = $(LIBS) $(INCS) $(FLAGS) #$(WINDOWS) $(RELEASE)

OBJS = src/main.cpp

all:
	$(CPP) $(OBJS) $(BUILDFLAGS) -o $(BIN)