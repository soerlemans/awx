# Exported variables:
export SRC := src
export BUILD := build

export EXECUTABLE := awx

# Compiler settings:
WARNINGS := -Wall -Wextra
CXXSTD := -std=c++2b
CXXFLAGS := $(CXXSTD) -O2 $(WARNINGS)

CXX := clang++

# Local variables:
SOURCES := $(wildcard $(SRC)/*.cpp)
HEADERS := $(wildcard $(SRC)/*.hpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SOURCES))

# Rules:
$(EXECUTABLE): $(OBJECTS)
	@echo $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $(EXECUTABLE)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@


# Phony rules:
.PHONY := clean
clean:
	$(RM) $(BUILD)/*
	$(RM) $(EXECUTABLE)
