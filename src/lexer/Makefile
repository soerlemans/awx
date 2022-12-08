# Local variables
# Destination directory for these object files
DEST = $(TOPDIR)/$(BUILD)/lexer

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

TOP_SOURCES += SOURCES
TOP_HEADERS += HEADERS
TOP_OBJECTS += OBJECTS

# Rules:
all: $(DEST)/ $(OBJECTS)

$(DEST)/:
	mkdir -p $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all $(SUBDIRS)
