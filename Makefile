# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=DEBUG

# Rules:
.PHONY: all \
	build debug \
	no-cmake \
	install clean \
	format lint \
	docs docs-pdf

all: build
build:
	cmake -S . -B $@/
	cmake --build $@/

debug:
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

# Build option if your system does not have CMake
no-cmake:
	$(MAKE) -f make/backup.mk

# After build rules:
install: build
	@echo "TODO: Implement"

clean:
	rm -rf build/*
	rm -rf debug/*

# Misc. rules:
format:
	find src/ -iname "*.[ch]pp" -exec clang-format {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy {} -- -DDEVELOPMENT \;

# Documentation rules:
docs:
	doxygen docs/Doxyfile

# Compile documentation as LaTex
docs-pdf: docs
	cd doxygen/latex/ && $(MAKE)


