# Local variables
# Destination directory for these object files
DEST = $(TOPDIR)/$(BUILD)

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.hpp)
OBJECTS := $(patsubst %.cpp,$(DEST)/%.o,$(SOURCES))

TOP_SOURCES += SOURCES
TOP_HEADERS += HEADERS
TOP_OBJECTS += OBJECTS

# SUBDIRS := $(wildcard */.)

# Rules:
# all: $(SUBDIRS) $(OBJECTS)

# $(SUBDIRS):
# 	$(MAKE) -C $@

# .PHONY: all $(SUBDIRS)

all: lexer/ parser/ $(OBJECTS)

lexer/:
	$(MAKE) -C $@ -f lexer.mk

parser/:
	$(MAKE) -C $@ -f parser.mk

$(DEST)/main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(DEST)/%.o: %.cpp %.hpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# Phony targets
.PHONY: all lexer/ parser/ $(SUBDIRS)
