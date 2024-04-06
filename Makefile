CXX = clang++
CXXFLAGS = -std=c++17 -g
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests
EXTERNAL_DIR = external

# Main program sources and executable
MAIN_SRC = $(SRC_DIR)/main.cpp
MAIN_OBJ = $(BIN_DIR)/main.o 
SRCS = $(filter-out $(MAIN_SRC), $(wildcard $(SRC_DIR)/*.cpp))
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXEC = ./main

# Test sources and executable
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXEC = $(BIN_DIR)/test_exe

all: $(EXEC)
	@echo "Compilation complete"

# Compile the main executable
$(EXEC): $(MAIN_OBJ) $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile source files to object files for main
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile source files to object files for geohash
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile and run tests
test: $(OBJS) $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -I$(EXTERNAL_DIR) $^ -o $(TEST_EXEC)
	@./$(TEST_EXEC)

clean: 
	@rm -rf $(BIN_DIR) *.o $(EXEC)