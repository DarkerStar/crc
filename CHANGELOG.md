# Change log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Added
- `CHANGELOG.md` file: change log.
- `LICENSE` file: project licence (contains
  [GPLv3.0](https://www.gnu.org/licenses/gpl.html)).
- `README.md` file: project information.
- `Makefile` file: root makefile, which does nothing much except running
  tests and passing test commands to the test makefile to build the
  tests.
- `indi/crc.hpp` file: the actual header file that this project is all
  about.
- `indi/crc-io.hpp` file: I/O and string formatting routines for CRCs.
- `test/Makefile` file: test makefile, which builds the tests.
- `test/test-main.cpp` file: main source code file for the tests.
- `test/polynomials.cpp` file: tests for polynomial values and
  functions.
- `test/polynomials-id.cpp` file: tests for polynomial I/O and string
  formatting.
