CC=clang++
SOURCES=$(wildcard source/*.cpp)
OBJECTS=$(addprefix bin/, $(notdir $(SOURCES:.cpp=.o)))
EXE=bin/varuna
LIBS=sdl2 SDL2_image
CFLAGS=-std=c++11 -Wall -g -I ./include `pkg-config --cflags $(LIBS)`
LDFLAGS=`pkg-config --libs --static $(LIBS)`
MAC_LDFLAGS=-lSOIL -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

# if mac, add framework references
ifneq ($(OS), WINDOWS_NT)
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME), Darwin)
		LDFLAGS += $(MAC_LDFLAGS)
	endif
endif

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LDFLAGS)

$(OBJECTS): $(SOURCES)
	@echo Compiling $@
	$(CC) $(CFLAGS) -c $(patsubst %.o, %.cpp, source/$(notdir $@)) -o $@

clean:
	rm -f $(EXE)
	rm -f $(OBJECTS)
