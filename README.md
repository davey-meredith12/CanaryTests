# CanaryTests
A testing framework designed in C++.
Built to understand how other testing frameworks like **GoogleTest** works under the hood.

## Features
- Test registration using 'TEST(suite, name)'.
- Test suites for grouping related categories.
- Automatic static test registration.
- Colored test output.
- Failure reporting with file name and line number.
- Expect assertions that are non-fatal.
- Summary of tests run, passed, and failed.

## Assertions
Currently supported assertions

| Assertion | Description |
| --- | --- |
| `EXPECT_TRUE(condition)` | Expects a condition to be `true` |
| `EXPECT_FALSE(condition)` | Expects a condition to be `false` |
| `EXPECT_EQ(a, b)` | Expects two values to be equal |
| `EXPECT_NE(a, b)` | Expects two values to be different |
| `EXPECT_LT(a, b)` | Expects `a` to be less than `b` |
| `EXPECT_LE(a, b)` | Expects `a` to be less than or equal to `b` |
| `EXPECT_GT(a, b)` | Expects `a` to be greater than `b` |
| `EXPECT_GE(a, b)` | Expects `a` to be greater than or equal to `b` |
| `EXPECT_NEAR(a, b, error)` | Expects two values to be within a specified absolute error (signed only)|

Assertions are non-fatal.