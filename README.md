AWX
===
Awx is an acronym for "Awk With eXtensions".
It is meant to be an improved version of AWK with some more shiny features and the ability to add extensions/libraries, whilst still remaining (mostly) true to POSIX AWK.

Awx is written in C++ for the following reasons:
 + C++ is fast
 + C++ has a large standard library
 + Most systems come with a C++ compiler
 + C++ is very stable and offers a lot of compatibility with other languages

The reasons why Rust is not considered suitable:
 + Slightly slower than C++
 + Most systems do not come with a Rust compiler
 + Rust pulls a lot of dependencies
 + No large benefit out of the memory safety that Rust supplies
   + Most of awx input will come from files or pipes, meaning that it being abused by a malicious user is significantly less likely to happen
     (it would still be possible that somebody uses the program irresponsibly)
   + `cppfront` and `valgrind` will be used to weed out memory errors

Goals Awx aims to achieve:
 + Be as fast as possible
 + Be extremely lightweight
 + Add scoping to variables
 + Implement some high level language constructs
 + Maintain some level of AWK compatibility

Features
--------
Our aim is to implement the following features in AWX:
 + Assignable rules
 + Nested rules
 + Scoping
 + Modules
 + Compilable `.awx` files
 + Extended regular expressions support
 + Perl regular expressions support

Features so far implemented:
 + Absolutely none

Getting AWX
-----------
### Dependencies
We aim to keep dependencies to a minimum.
But the following packages are required:
 + A C++ compiler (clang, g++ or msvc++)
   + Must support C++23

### Build

### Install

Contributing
------------
This section is for those who want to contribute to the project.

### Dependencies
The following dependencies are required:
 + A C++ compiler (clang, g++ or msvc++)
   + Must support C++23
 + `clang-format`
 + `valgrind`
 + `cppfront` (if this works out)
 + `doxygen`

### Style guide
For the style guide look into `docs/styleguide.md`.
