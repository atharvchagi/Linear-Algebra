# High-Performance Linear Algebra Library Makefile
# Atharv Chagi

CXX = g++
CXXFLAGS = -std=c++17 -O3 -march=native -flto -DNDEBUG
DEBUG_FLAGS = -std=c++17 -g -O0 -Wall -Wextra -Wpedantic
INCLUDES = -I.
LIBS = 

# Directories
SRC_DIR = .
BUILD_DIR = build
BIN_DIR = bin

# Source files
SOURCES = main.cpp PerformanceBenchmark.cpp
HEADERS = Matrix.h Matrix.cpp Vector.h Vector.cpp PerformanceBenchmark.h

# Target executables
TARGET = $(BIN_DIR)/linalg
DEBUG_TARGET = $(BIN_DIR)/linalg_debug
LEGACY_TARGETS = $(BIN_DIR)/matrixmult $(BIN_DIR)/determinant $(BIN_DIR)/eigenvalues $(BIN_DIR)/dotproduct $(BIN_DIR)/crossproduct

# Object files
OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%.o)
DEBUG_OBJECTS = $(SOURCES:%.cpp=$(BUILD_DIR)/%_debug.o)

# Default target
all: directories $(TARGET) legacy

# Debug build
debug: directories $(DEBUG_TARGET)

# Performance optimized build
performance: CXXFLAGS += -funroll-loops -ffast-math -mtune=native
performance: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

# Main target (optimized)
$(TARGET): $(OBJECTS)
	@echo "Linking optimized executable..."
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(LIBS)
	@echo "Built optimized executable: $(TARGET)"

# Debug target
$(DEBUG_TARGET): $(DEBUG_OBJECTS)
	@echo "Linking debug executable..."
	$(CXX) $(DEBUG_FLAGS) $(DEBUG_OBJECTS) -o $@ $(LIBS)
	@echo "Built debug executable: $(DEBUG_TARGET)"

# Compile optimized object files
$(BUILD_DIR)/%.o: %.cpp $(HEADERS)
	@echo "Compiling $< (optimized)..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile debug object files
$(BUILD_DIR)/%_debug.o: %.cpp $(HEADERS)
	@echo "Compiling $< (debug)..."
	$(CXX) $(DEBUG_FLAGS) $(INCLUDES) -c $< -o $@

# Legacy executables (using old code for compatibility)
legacy: $(LEGACY_TARGETS)

$(BIN_DIR)/matrixmult: matrixmult.cpp
	@echo "Building legacy matrix multiplication..."
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/determinant: determinant.cpp linalg.h
	@echo "Building legacy determinant calculator..."
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/eigenvalues: eigenvalues.cpp linalg.h
	@echo "Building legacy eigenvalue calculator..."
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/dotproduct: dotproduct.cpp linalg.h
	@echo "Building legacy dot product calculator..."
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/crossproduct: crossproduct.cpp linalg.h
	@echo "Building legacy cross product calculator..."
	$(CXX) $(CXXFLAGS) -o $@ $<

# Run the main program
run: $(TARGET)
	@echo "Running High-Performance Linear Algebra Library..."
	./$(TARGET)

# Run benchmark suite
benchmark: $(TARGET)
	@echo "Running performance benchmarks..."
	echo "9" | ./$(TARGET)

# Run debug version
run-debug: $(DEBUG_TARGET)
	@echo "Running debug version..."
	./$(DEBUG_TARGET)

# Performance tests
test-performance: $(TARGET)
	@echo "Running performance comparison tests..."
	@echo "Testing matrix multiplication performance:"
	@time echo -e "1\n100\n100\n100\n100\n$(shell yes 1.0 | head -20000 | tr '\n' ' ')\n0" | ./$(TARGET) > /dev/null
	@echo "Performance test completed."

# Clean build files
clean:
	@echo "Cleaning build files..."
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Clean completed."

# Install (copy to system path)
install: $(TARGET)
	@echo "Installing to /usr/local/bin..."
	sudo cp $(TARGET) /usr/local/bin/linalg
	@echo "Installation completed."

# Uninstall
uninstall:
	@echo "Uninstalling from /usr/local/bin..."
	sudo rm -f /usr/local/bin/linalg
	@echo "Uninstallation completed."

# Help
help:
	@echo "High-Performance Linear Algebra Library Build System"
	@echo "===================================================="
	@echo "Available targets:"
	@echo "  all          - Build optimized executable and legacy programs"
	@echo "  debug        - Build debug version with debugging symbols"
	@echo "  performance  - Build with maximum performance optimizations"
	@echo "  legacy       - Build legacy individual calculators"
	@echo "  run          - Build and run the main program"
	@echo "  run-debug    - Build and run debug version"
	@echo "  benchmark    - Run performance benchmarks"
	@echo "  test-performance - Run performance comparison tests"
	@echo "  clean        - Remove all build files"
	@echo "  install      - Install to system path"
	@echo "  uninstall    - Remove from system path"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Compiler optimizations used:"
	@echo "  -O3          - Maximum optimization level"
	@echo "  -march=native - Optimize for current CPU architecture"
	@echo "  -flto        - Link-time optimization"
	@echo "  -funroll-loops - Unroll loops for better performance"
	@echo "  -ffast-math  - Fast math optimizations"

# Check compiler and system info
info:
	@echo "System Information:"
	@echo "==================="
	@echo "Compiler: $(CXX)"
	@$(CXX) --version | head -1
	@echo "CPU Info:"
	@lscpu | grep "Model name" || echo "CPU info not available"
	@echo "Memory Info:"
	@free -h | grep "Mem:" || echo "Memory info not available"
	@echo "Optimization flags: $(CXXFLAGS)"

# Phony targets
.PHONY: all debug performance directories legacy run run-debug benchmark test-performance clean install uninstall help info

# Default goal
.DEFAULT_GOAL := all
