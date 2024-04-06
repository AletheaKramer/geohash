CXX = clang++
CXXFLAGS = -std=c++17 -g
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests
EXTERNAL_DIR = external

# Main program sources and executable
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXEC = $(BIN_DIR)/geohash

# Test sources and executable
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_EXEC = $(BIN_DIR)/test_exe

all: $(EXEC)
	@echo "Compilation complete"

# Compile and run tests
test: $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -I$(EXTERNAL_DIR) $^ -o $(TEST_EXEC)
	@./$(TEST_EXEC)

# Compile the main executable
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Compile source files to object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
	@rm -rf $(BIN_DIR)
