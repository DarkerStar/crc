# Change log
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/) 
and this project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]

## 0.1.0 - 2016-09-27
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
- `test/calculate.cpp` file: tests for CRC calculation.
- `test/calculate-next.cpp` file: tests for calculating a single CRC.
- `test/calculate-raw.cpp` file: tests for raw CRC calculation.
- `test/crc-type.cpp` file: tests for CRC type.
- `test/generate-table.cpp` file: tests for generating lookup tables.
- `test/polynomials.cpp` file: tests for polynomial values and
  functions.
- `test/polynomials-id.cpp` file: tests for polynomial I/O and string
  formatting.
- `test/data/table-crc16` file: test lookup table values for CRC16.
- `test/data/table-crc16-ccitt` file: test lookup table values for
  CRC16-CCITT.
- `test/data/table-crc32` file: test lookup table values for CRC32.
- `test/data/table-crc32c` file: test lookup table values for CRC32c.
- `test/data/table-crc64-ecma` file: test lookup table values for
  CRC64-ECMA.

[Unreleased]: https://github.com/DarkerStar/crc/compare/v0.1.0...HEAD
