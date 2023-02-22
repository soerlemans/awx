# Variables:
# Important build information
export SRC := src
export BUILD := build

export EXECUTABLE := awx

# Compiler settings:
export WARNINGS := -Wall -Wextra -pedantic
export CXXSTD := -std=c++2b
export CXXFLAGS := $(CXXSTD) -O2 $(WARNINGS)

export CXX := clang++

# We must have the find command available
SOURCES := $(shell find $(SRC)/ -name '[^.]*.cpp')
OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)

# Rules:
all: $(BUILD)/$(EXECUTABLE)

$(BUILD)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	$(RM) -r $(BUILD)/*
	$(RM) $(BUILD)/$(EXECUTABLE)
