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

# Dependencies directory name.
depsdir := .deps

# Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
exe := crc-test

src := test-main.cpp \
       generate-table.cpp \
       polynomials.cpp \
       polynomials-io.cpp

depsdir := .deps

# Generated values ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
obj := ${src:.cpp=.o}
dep := $(addprefix ${depsdir}/,${src:.cpp=.d})

CPPFLAGS += -I ..
LDLIBS   += -lboost_unit_test_framework

# Default target ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY : all
all : ${exe}

# Test executable ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
${exe} : ${obj}
	${CXX} ${CPPFLAGS} ${CXXFLAGS} ${LDFLAGS} ${^} ${LDLIBS} -o ${@}

# Compile target ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Compile .cpp files, but at the same time create dependency info for
# each file.
# 
# Some tweaking of the dependency files is needed to turn:
#     x.o : x.cpp <other dependencies>
# into:
#     .depsdir/x.d x.o : x.cpp <other dependencies>
# so that the dependency info also depends on the source file (for the
# rare situation that the object file is up to date, but the dependency
# file has been reverted to an older version, and thus some change in
# the dependency chain is not caught).
${obj} : %.o : %.cpp
	@mkdir -p "${depsdir}/${@D}"
	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c -MMD -o ${@} ${<}
	@{ printf '%s ' "${depsdir}/${*}.d" ; cat "${*}.d" ; } >"${depsdir}/${*}.d"
	@rm "${*}.d"

# Include dependency info (if previously generated).
-include $(addprefix ${depsdir}/,${src:.cpp=.d})

# Clean target ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
.PHONY : clean
clean : 
	-@rm -rf ${depsdir}
	-@rm -f ${obj}
	-@rm -f ${exe}
