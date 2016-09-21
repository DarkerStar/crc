# This file is part of indi-crc.
# 
# indi-crc is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# indi-crc is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with indi-crc.  If not, see <http://www.gnu.org/licenses/>.

# Make environment settings ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Always a good idea to specify the shell, just in case.
SHELL := /bin/sh

# Restrict the suffixes to the ones used by C++ (plus dependency files).
.SUFFIXES:
.SUFFIXES: .cpp .hpp .o .d

# Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
testdir := test
testexe := crc-test

# Default target ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Nothing to do here.
.PHONY : all
all : 

# Test targets ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# "make test" target makes the tests then runs them.
.PHONY : test
test : test-build-only
	${testdir}/${testexe}

# "make test-build-only" target makes the tests but does not run them.
.PHONY : test-build-only
test-build-only :
	@$(MAKE) -C ${testdir} ${testexe}

# Clean target ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Nothing to clean here, so just recurse into the tests and clean there.
.PHONY : clean
clean : 
	@$(MAKE) -C ${testdir} ${@}
