# Variables:
DEBUG := -DCMAKE_BUILD_TYPE=DEBUG

# Rules:
.PHONY: all build debug format lint no-cmake

all: build
build:
	cmake -S . -B $@/
	cmake --build $@/

debug:
	cmake -S . -B $@/ $(DEBUG)
	cmake --build $@/

format:
	find src/ -iname "*.[ch]pp" -exec clang-format {} \;

lint:
	find src/ -iname "*.[ch]pp" -exec clang-tidy {} -- -DDEVELOPMENT \;

# Build option if your system does not have CMake
no-cmake:
	$(MAKE) -f make/backup.mk

clean:
	rm -rf build/*
	rm -rf debug/*
