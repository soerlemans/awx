# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=DEBUG

.DEFAULT_GOAL := build

# Rules:
.PHONY: all \
	build debug \
	install clean \
	format lint \
	docs docs-pdf

all: build debug
build:
	cmake -S . -B $@/
	cmake --build $@/

debug:
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

# After build rules:
install: build
	@echo "TODO: Implement"

clean:
	rm -rf build/*
	rm -rf debug/*

# Misc. rules:
format:
	find src/ -iname "*.[ch]pp" -exec clang-format -i {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy {} -- -DDEVELOPMENT \;

header_guard:
	find src/ -iname "*.hpp" -exec ./tools/header_guard.awk {} \;

# Documentation rules:
docs:
	doxygen docs/Doxyfile

# Compile documentation as LaTex
docs-pdf: docs
	cd doxygen/latex/ && $(MAKE)
