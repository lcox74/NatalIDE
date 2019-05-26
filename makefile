CPP = g++.exe
LIBS = -L"Dependencies/SDL2/lib"
INCS = -I"Dependencies/SDL2/include"
FLAGS = -lmingw32 -luser32 -lSDL2main -lSDL2
BIN = bin/NatalIDE.exe
WINDOWS = -mwindows #Add to get rid of command console
RELEASE = -Wall -O2 # Add for release version... Should run faster than normal... Should.

BUILDFLAGS = $(LIBS) $(INCS) $(FLAGS) #$(WINDOWS) $(RELEASE)

OBJS = src/main.cpp

# $(BIN) : $(OBJS)
# 	$(CPP) $(OBJS) $(BUILDFLAGS) -o $(BIN)

# src/main.o : src/main.cpp
# 	$(CPP) $(BUILDFLAGS) -c src/main.cpp
$(BIN) : $(OBJS)
	$(CPP) $(OBJS) $(BUILDFLAGS) -o $(BIN)