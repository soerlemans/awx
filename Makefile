# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=Debug
RELWITHDEBINFO := -DCMAKE_BUILD_TYPE=RelWithDebInfo

.DEFAULT_GOAL := build

# Rules:
.PHONY: all \
	build debug benchmark \
	install clean \
	format lint \
	docs docs-pdf

all: build debug benchmark
build: # Release build
	cmake -S . -B $@/
	cmake --build $@/

debug: # Build used for debugging and analyzing
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

benchmark: # Build used for profiling and optimization
	cmake -S . -B $@/ $(RELWITHDEBINFO)
	cmake --build $@/

# After build rules:
install: build
	@echo "TODO: Implement"

clean:
	rm -rf build/*
	rm -rf debug/*
	rm -rf benchmark/*

# Misc. rules:
format:
	find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy {} -- -DDEBUG \;

header_guard:
	find src/ -iname "*.hpp" -exec ./tools/header_guard.awk {} \;

# Documentation rules:
docs:
	doxygen docs/Doxyfile

# Compile documentation as LaTex
docs-pdf: docs
	cd doxygen/latex/ && $(MAKE)
