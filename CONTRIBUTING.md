# Contributing
This section is for those who want to contribute to the project.

## Dependencies
The following dependencies are required in order to contribute:

- C++ compiler (clang, g++ or msvc++)
  - Must support C++23
- Make (Used to invoke CMake and scripts)
- [Cmake](https://cmake.org/) (Main buildsysstem)
- [CLI11](https://github.com/CLIUtils/CLI11) (CLI option parsing library)
- [tabulate](https://github.com/p-ranav/tabulate) (Text table library)
- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [clang-tidy](https://clang.llvm.org/extra/clang-tidy/)
- [doxygen](https://www.doxygen.nl/)
- [valgrind](https://valgrind.org/) (Used for profiling)

You can install all required dependencies with the following aptitude command:

```shell
apt install -y build-essential cmake libcli11-dev clang-format clang-tidy doxygen valgrind
```

## Style guide
TODO: For the style guide look into `docs/styleguide.md`.

## Architecture
TODO: For a short description of the architecture of the software look into `docs/architecture.md`.
