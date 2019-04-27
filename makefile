OUTPUT_DIR= bin
COMPILER = g++
COMPILER_FLAGS=-w
SOURCE_DIR = source/
INCLUDES_DIR =-I includes/
LINKER_FLAGS =-lSDL2 -lGL -lGLU -lpthread
LIBRARY_FLAGS= -std=c++11 -c -fPIC -shared
SERVER_LIB=$(OUTPUT_DIR)/server.so
CLIENT_LIB=$(OUTPUT_DIR)/client.so
all: game | client_driver | server_driver

game:	$(SOURCE_DIR)game.cpp | make_dir
	$(COMPILER) $(INCLUDES_DIR) $(SOURCE_DIR)game.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/game.out
client_lib: $(SOURCE_DIR)client.cpp | make_dir
	$(COMPILER) $(LIBRARY_FLAGS) $(INCLUDES_DIR) $(SOURCE_DIR)client.cpp -lpqxx -o $(CLIENT_LIB)
client_driver: $(SOURCE_DIR)client_driver.cpp | client_lib
	$(COMPILER) $(INCLUDES_DIR) $(CLIENT_LIB) $(SOURCE_DIR)client_driver.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/client.out
server_lib: $(SOURCE_DIR)server.cpp | make_dir
	$(COMPILER) $(LIBRARY_FLAGS) $(INCLUDES_DIR) $(SOURCE_DIR)server.cpp -lpqxx -o $(SERVER_LIB)
server_driver: $(SOURCE_DIR)server_driver.cpp | server_lib
	$(COMPILER) $(INCLUDES_DIR) $(SERVER_LIB) $(SOURCE_DIR)server_driver.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/server.out
make_dir:
	mkdir -p $(OUTPUT_DIR)
