# Local variables:
DEST := $(BUILD)/parser/node

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

# Rules:
all: operators $(DEST)/ $(OBJECTS)

operators:
	$(MAKE) -C $@/

$(DEST)/:
	mkdir -p $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all operators
