# Exported variables:
# Important build information
export SRC := src
export BUILD := build

export EXECUTABLE := awx

# Compiler settings:
export WARNINGS := -Wall -Wextra -pedantic
export CXXSTD := -std=c++2b
export CXXFLAGS := $(CXXSTD) -g3 -DDEVELOPMENT -O2 $(WARNINGS)

export CXX := clang++

# TODO: Find a way around the shell escape
SOURCES := $(shell find $(SRC)/ -name '*.cpp')
OBJECTS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SOURCES))

# Rules:
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)



.PHONY: all clean
clean:
	$(RM) -r $(BUILD)/*
	$(RM) $(EXECUTABLE)
