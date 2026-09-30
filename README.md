# Contest library

C++ algorithms and data structures for programming competitions, with tests
and a compact Typst reference handbook.

## Commands

Requirements: a C++20 compiler, GNU Make, and [Typst](https://typst.app/).

```sh
make test       # compile and run every tests/*_test.cpp
make handbook   # write build/handbook.pdf
make            # do both
```

Every push and pull request runs the tests and builds the handbook in GitHub
Actions. The PDF is available from the workflow run as the `contest-handbook`
artifact.

## Adding an algorithm

1. Add the reusable implementation under a topic directory such as `graph/`.
2. Add `tests/<name>_test.cpp`; each test file is built as its own executable.
   Include `tests/test.hpp` for `EXPECT_EQ`, and include the implementation you
   are testing.
3. Add a short Typst entry below `docs/content/`, then include it from
   `docs/handbook.typ`. Use the `algorithm` helper to attach notes and embed the
   source file, ensuring the tested code and printed code stay identical.

The checked-in algorithm files are snippets rather than complete submissions;
add the usual input/output `main` when using one in a contest problem.
