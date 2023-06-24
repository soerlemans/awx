# AWX

Awx is an acronym for "Awk With eXtensions".
It is meant to be an improved version of AWK with some more shiny features and the ability to add extensions/libraries, whilst aiming to be a drop in replacement for POSIX AWK.

Goals Awx aims to achieve:

- Be fast
- Add features to make AWk scale better for bigger projects
  - Add scoping to variables
- Maintain POSIX AWK compatibility

## Features

Our aim is to implement the following features in AWX:

- Default arguments
- Assignable rules
- Nested rules
- Byte compilation
- Modules

## Getting AWX

### Dependencies

We aim to keep dependencies to a minimum.
But the following packages are required:

- C++ compiler (clang, g++ or msvc++)
  - Must support C++23
- Cmake (You can build with just Make)
- Make
- CLI11 (Used for CLI argument handling)

### Build

Just run the following:

```
make -j
```

### Install

## Contributing

This section is for those who want to contribute to the project.

### Dependencies

The following dependencies are required:

- C++ compiler (clang, g++ or msvc++)
  - Must support C++23
- `clang-format`
- `clang-tidy`
- `doxygen`

### Style guide

For the style guide look into `docs/styleguide.md`.

## Credit

I sourced some scripts from Tim Sherwood for the purpose of testing the implementation.
I got them from his personal website [Some Useful Gawk Scripts](https://sites.cs.ucsb.edu/~sherwood/awk/).
I also took a script from [learnxinyminutes](https://learnxinyminutes.com/docs/awk/);
