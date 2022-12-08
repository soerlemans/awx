# Exported variables:
# Important build information
export TOPDIR := $(PWD)
export BUILD := build

export SRC := src
# export DEST = $(TOPDIR)/$(BUILD)

export EXECUTABLE := awx

# Compiler settings:
export WARNINGS := -Wall -Wextra -pedantic
export CXXSTD := -std=c++2b
export CXXFLAGS := $(CXXSTD) -g3 -O2 $(WARNINGS)

export CXX := clang++

# TODO: Find a way around the shell escape
SOURCES := $(shell find $(SRC)/ -name '*.cpp')
OBJECTS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SOURCES))

# Rules:
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)

$(OBJECTS): src

src:
	$(MAKE) -C $@/

.PHONY: all src clean
clean:
	$(RM) -r $(BUILD)/*
	$(RM) $(EXECUTABLE)
