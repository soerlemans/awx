# Local variables:
DEST := $(BUILD)/parser

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

# Rules:
all: statement $(DEST)/ $(OBJECTS)

statement:
	$(MAKE) -C $@/

$(DEST)/:
	mkdir -p $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all statement
