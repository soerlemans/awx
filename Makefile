# Exported variables:
# Important build information
export SRC := src
export BUILD := build

export EXECUTABLE := awx

# Compiler settings:
export WARNINGS := -Wall -Wextra -pedantic
export CXXSTD := -std=c++2b
# TODO: Add if eq statement for development
#export CXXFLAGS := $(CXXSTD) -O2 $(WARNINGS)
export CXXFLAGS := $(CXXSTD) -g3 -DDEVELOPMENT $(WARNINGS)

export CXX := clang++
# export CXX := g++

# TODO: Find a way around the shell escape
SOURCES := $(shell find $(SRC)/ -name '[^.]*.cpp')
OBJECTS := $(SOURCES:$(SRC)/%.cpp=$(BUILD)/%.o)

# Rules:
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD)/%.o: $(SRC)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean
clean:
	$(RM) -r $(BUILD)/*
	$(RM) $(EXECUTABLE)
