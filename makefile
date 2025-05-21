-include local.mk

# Default SDL paths and libs (can be overridden)
SDL_INCLUDE ?= /opt/homebrew/opt/sdl3/include
SDL_TTF_INCLUDE ?= /opt/homebrew/opt/sdl3_ttf/include
SDL_LIB ?= /opt/homebrew/opt/sdl3/lib
SDL_TTF_LIB ?= /opt/homebrew/opt/sdl3_ttf/lib

INCLUDES := -I$(SDL_INCLUDE) -I$(SDL_TTF_INCLUDE)
LDFLAGS := -L$(SDL_LIB) -L$(SDL_TTF_LIB)
LDLIBS := -lSDL3.0 -lSDL3_ttf

CXX ?= g++
CXXFLAGS ?= -std=c++14

# Source files and matching object files in build/
SRC := $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))

OUT := test

MKDIR_P ?= mkdir -p
RM ?= rm -f

all: $(OUT)
	./$(OUT)

# Link the final binary
$(OUT): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Compile .cpp to build/.o and create directories as needed
build/%.o: src/%.cpp
	@$(MKDIR_P) $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r build $(OUT)
