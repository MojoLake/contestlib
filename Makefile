CXX ?= g++
CXXFLAGS ?= -std=c++20 -O2 -Wall -Wextra -Wconversion -pedantic
TYPST ?= typst

TEST_SOURCES := $(wildcard tests/*_test.cpp)
TEST_BINARIES := $(patsubst tests/%_test.cpp,build/tests/%_test,$(TEST_SOURCES))
LIB_SOURCES := $(wildcard graph/*.cpp)
DOC_SOURCES := $(shell find docs -type f -name '*.typ') $(LIB_SOURCES)

.PHONY: all test handbook clean

all: test handbook

test: $(TEST_BINARIES)
	@set -e; for test_binary in $(TEST_BINARIES); do ./$$test_binary; done

build/tests/%_test: tests/%_test.cpp tests/test.hpp $(LIB_SOURCES)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -o $@

handbook: build/handbook.pdf

build/handbook.pdf: $(DOC_SOURCES)
	@mkdir -p $(@D)
	$(TYPST) compile --root . docs/handbook.typ $@

clean:
	rm -rf build
