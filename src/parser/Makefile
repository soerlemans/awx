# Local variables:
DEST := $(BUILD)/parser

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

# Rules:
all: node $(DEST)/ $(OBJECTS)

node:
	$(MAKE) -C $@/

$(DEST)/:
	mkdir -p $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all node
