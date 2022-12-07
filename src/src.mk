# Local variables
# Destination directory for these object files
DEST = $(TOPDIR)/$(BUILD)

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

# Rules:
all: lexer parser $(OBJECTS)

lexer:
	$(MAKE) -C $@/ -f $@.mk

parser:
	$(MAKE) -C $@/ -f $@.mk

$(DEST)/main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all lexer parser $(SUBDIRS)
