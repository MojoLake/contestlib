#pragma once

#include <iostream>
#include <string_view>

namespace test {
inline int failures = 0;

template <class Actual, class Expected>
void expect_eq(const Actual& actual, const Expected& expected,
               std::string_view expression, std::string_view file, int line) {
    if (actual == expected) return;
    std::cerr << file << ':' << line << ": expected " << expression << " == "
              << expected << ", got " << actual << '\n';
    ++failures;
}
}  // namespace test

#define EXPECT_EQ(actual, expected)                                           \
    ::test::expect_eq((actual), (expected), #actual, __FILE__, __LINE__)
