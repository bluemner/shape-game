OUTPUT_DIR= bin
COMPILER = g++
COMPILER_FLAGS=-w -std=c++11
SOURCE_DIR = source/
INCLUDES_DIR =-I includes/
LINKER_FLAGS =-lSDL2 -lGL -lGLU -lpthread
LIBRARY_FLAGS= -std=c++11 -c -fPIC -shared
SERVER_LIB=$(OUTPUT_DIR)/server.so
CLIENT_LIB=$(OUTPUT_DIR)/client.so
all: game | driver

driver: client_driver | server_driver

client_lib: $(SOURCE_DIR)client.cpp | make_dir
	$(COMPILER) $(LIBRARY_FLAGS) $(INCLUDES_DIR) $(SOURCE_DIR)client.cpp -lpqxx -o $(CLIENT_LIB)
client_driver: $(SOURCE_DIR)client_driver.cpp | client_lib
	$(COMPILER) $(INCLUDES_DIR) $(CLIENT_LIB) $(SOURCE_DIR)client_driver.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/client.out
game:	$(SOURCE_DIR)game.cpp | client_lib 
	$(COMPILER) $(INCLUDES_DIR) $(SOURCE_DIR)game.cpp $(CLIENT_LIB) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/game.out
server_lib: $(SOURCE_DIR)server.cpp | make_dir
	$(COMPILER) $(LIBRARY_FLAGS) $(INCLUDES_DIR) $(SOURCE_DIR)server.cpp -lpqxx -o $(SERVER_LIB)
server_driver: $(SOURCE_DIR)server_driver.cpp | server_lib
	$(COMPILER) $(INCLUDES_DIR) $(SERVER_LIB) $(SOURCE_DIR)server_driver.cpp $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OUTPUT_DIR)/server.out
make_dir:
	mkdir -p $(OUTPUT_DIR)
