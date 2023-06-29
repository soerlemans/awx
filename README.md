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

## Progress
Awx is currently in active development and not very mature but the following has already been implemented:

- [x] Reading input from standard in and from files
- [x] Passing programs via command line and from files
- [x] Correctly handling the precedence and associativity of expressions
- [x] Operators (unary prefixes, arithmetic, string concatenation, comparisons, match, membership, logical, ternary, assignment, postcrement)
- [x] Recipes (body is executed when the record matches the regex expression)
- [x] Control statements (if, for, while, do while, return, continue, break, next, exit)
- [x] Functions (calling functions as well as defining functions)
- [x] Fieldreferences (currently the field separator is always set to be a space)
- [x] Builtin variables (some)
- [x] Rudimentary benchmarking (measuring total execution time as well as lexing, parsing, execution)

Important features that must still be implemented:

- [] Some bug fixes
- [] Implementing builtin functions
- [] Bytecode compilation
- [] Common optimizations
- [] Benchmarking using [FlameGraph](https://github.com/brendangregg/FlameGraph)
- [] Displaying data about AST in a table

## Getting AWX
### Dependencies
Awx aims to keep dependencies to a minimum.
But the following packages are required:

- C++ compiler (clang, g++ or msvc++)
  - Must support C++23
- Make (Used to invoke CMake and scripts)
- Cmake  (Main buildsysstem)
- [CLI11](https://github.com/CLIUtils/CLI11) (CLI option parsing library)
- [tabulate](https://github.com/p-ranav/tabulate) (Text table library)

Tabulate is downloaded using CMake and statically linked but CLI11 is dynamically linked and CMake searches for it on your system.

### Build
```
make -j
```

The binary will then be in `build/awx`.
To get the help manual run `awx -h`.

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
TODO: For the style guide look into `docs/styleguide.md`.

### Architecture
TODO: For a short description of the architecture of the software look into `docs/architecture.md`.

## Credit
I sourced some scripts from Tim Sherwood for the purpose of testing the implementation.
I got them from his personal website [Some Useful Gawk Scripts](https://sites.cs.ucsb.edu/~sherwood/awk/).
I also took a script from [learnxinyminutes](https://learnxinyminutes.com/docs/awk/);

