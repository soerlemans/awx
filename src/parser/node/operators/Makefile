# Local variables:
DEST := $(BUILD)/parser/node/operators

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

# Rules:
all: $(DEST)/ $(OBJECTS)

$(DEST)/:
	mkdir -p $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all
