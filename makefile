OUTPUT_DIR= bin
COMPILER = g++
COMPILER_FLAGS=-w
SOURCE_DIR = source/
INCLUDES_DIR =-I includes/
LINKER_FLAGS =-lSDL2 -lGL -lGLU

all: game

game:	$(SOURCE_DIR)game.cpp | make_dir
	$(COMPILER) $(INCLUDES_DIR) $(SOURCE_DIR)game.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/game

make_dir:
	mkdir -p $(OUTPUT_DIR)
