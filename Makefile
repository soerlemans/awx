# Exported variables:
export SRC := src
export BUILD := build

export EXECUTABLE := awx

# Compiler settings:
WARNINGS := -Wall -Wextra
CXXSTD := -std=c++23
CXXFLAGS := $(CXXSTD) -O2 $(WARNINGS)

ifndef CXX
CXX := clang
endif

# Rules:
$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)

# Phony rules:
.PHONY := clean
clean:
	$(RM) $(BUILD)/*
	$(RM) $(EXECUTABLE)
