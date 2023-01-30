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
 + No large benefit out of the memory safety that Rust supplies

Goals Awx aims to achieve:
 + Be as fast as possible
 + Be lightweight
 + Add scoping to variables
 + Implement some high level language constructs
 + Maintain POSIX AWK compatibility
 + Add some new features that are backwards compatible

Features
--------
Our aim is to implement the following features in AWX:
 + Default arguments
 + Assignable rules
 + Nested rules
 + Extended regular expressions support
 + Perl regular expressions support
 + Byte compiled `.awx` files
 + Modules

Features so far implemented:
 + TODO: Implement features

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
 + `doxygen`

### Style guide
For the style guide look into `docs/styleguide.md`.

Credit
------
I sourced some scripts from Tim Sherwood for the purpose of testing the implementation.
I got them from his personal website [Some Useful Gawk Scripts](https://sites.cs.ucsb.edu/~sherwood/awk/).

TODO
----
+ Better diagnostics for the parsing errors
+ Tokens should know their position in a file (store it in some kind of struct)
+ Exceptions should have a better class structure for accurately displaying error information
+ Node classes may not be initialized with nullptrs
