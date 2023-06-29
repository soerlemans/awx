# Awx

Awx is an acronym for "AWK With eXtensions".
Awx is aimed to be a drop in replacement for AWK with some added extensions (this goal is very similar to GNU AWK).

Goals Awx aims to achieve:

- Be fast
- Add features to make AWK more powerful
  - Optional local scoping for variables
  - Default arguments and keyword arguments
  - Add namespaces
- Maintain POSIX AWK compatibility
- Expand on the standard library
- Support reading of common formats
  - CSV
  - JSON
  - XML
  - etc

## Getting AWX

### Dependencies

We aim to keep dependencies to a minimum.
But the following packages are required:

- C++ compiler (clang, g++ or msvc++)
  - Must support C++23
- Cmake (there is an option to build with just Make)
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

# Issues

Awx
