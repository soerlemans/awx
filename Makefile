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

# File's
export TOP_SOURCES
export TOP_HEADERS
export TOP_OBJECTS

# Rules:
all: subdirs $(EXECUTABLE)

subdirs:
	$(MAKE) -C $(SRC)/ -f src.mk

$(EXECUTABLE): $(TOP_OBJECTS)
	@echo Objects $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)

.PHONY: all subdirs clean
clean:
	$(RM) -r $(BUILD)/*
	$(RM) $(EXECUTABLE)
