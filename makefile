# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Targets
# Specify the output binary and object files to compile
TARGET = main.out
OBJS = main.o q1.o q2.o HashTable.o

# Default target to build the executable
default: $(TARGET)

# Rule to build the executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile each .cpp file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean up object and output files
clean:
	rm -f $(OBJS) $(TARGET)