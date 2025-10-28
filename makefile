# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Executable name
TARGET = matrix_program

# Source file
SRC = main.c++

# Default rule
all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run rule (optional)
run: $(TARGET)
	./$(TARGET)

# Clean rule
clean:
	rm -f $(TARGET)
