# CanaryTests
A testing framework designed in C++.
Built to understand how other testing frameworks like **GoogleTest** work under the hood.

## Features
- Test registration using 'TEST(suite, name)'.
- Test suites for grouping related categories.
- Test Fixtures for repeated set up and tear down steps
- Automatic static test registration.
- Colored test output.
- Failure reporting with file name and line number.
- Expect assertions that are non-fatal.
- Summary of tests run, passed, and failed.

## Tests

Both plain tests and fixture-based tests are supported. Every test is
registered automatically at static initialization time, so there is no
need to list them anywhere — just define them and call `RUN_ALL_TESTS()`
from `main`.

### `TEST(suite, name)`

Defines a standalone test. `suite` groups related tests together in the
output; `name` identifies the individual test. The body that follows the
macro is the test function.

```cpp
TEST(MathTests, AddsPositiveNumbers){
    EXPECT_EQ(2 + 2, 4);
}

TEST(MathTests, SubtractsNumbers){
    EXPECT_EQ(5 - 3, 2);
}
```

### `TEST_F(fixture, name)`

Defines a test that runs against a fixture. `fixture` must be a struct
that derives from `Test`. Before the test body runs, a fresh fixture
instance is constructed and its `SetUp()` is called; afterwards
`TearDown()` is called. Each `TEST_F` gets its own instance, so state
does not leak between tests.

```cpp
struct VectorTest : Test {
    std::vector<int> values;

    void SetUp() override {
        values = {1, 2, 3};
    }

    void TearDown() override {
        values.clear();
    }
};

TEST_F(VectorTest, StartsWithThreeElements){
    EXPECT_EQ(values.size(), 3u);
}

TEST_F(VectorTest, CanAppend){
    values.push_back(4);
    EXPECT_EQ(values.back(), 4);
}
```

Members of the fixture (`values` above) are accessible directly in the
test body, as if the body were a method of the fixture.

### Running the tests

```cpp
int main(){
    return RUN_ALL_TESTS();
}
```

`RUN_ALL_TESTS()` executes every registered test, prints a per-test
result and a summary, and returns `0` if all tests passed or `1`
otherwise.

## Assertions
Currently supported assertions

### Non-Fatal Assertions
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

### Fatal Assertions
| Assertion | Description |
| --- | --- |
| `ASSERT_TRUE(condition)` | Asserts a condition to be `true` |
| `ASSERT_FALSE(condition)` | Asserts a condition to be `false` |
| `ASSERT_EQ(a, b)` | Asserts two values to be equal |
| `ASSERT_NE(a, b)` | Asserts two values to be different |
| `ASSERT_LT(a, b)` | Asserts `a` to be less than `b` |
| `ASSERT_LE(a, b)` | Asserts `a` to be less than or equal to `b` |
| `ASSERT_GT(a, b)` | Asserts `a` to be greater than `b` |
| `ASSERT_GE(a, b)` | Asserts `a` to be greater than or equal to `b` |
| `ASSERT_NEAR(a, b, error)` | Asserts two values to be within a specified absolute error (signed only)|

## Exception Assertions
### Non-Fatal Assertions
| Assertion | Description |
| --- | --- |
| `EXPECT_THROW(statement, exception_type)` | Expects a statement to throw an exception of type `exception_type` |
| `EXPECT_ANY_THROW(statement)` | Expects statement to throw any exception |

### Fatal Assertions
| Assertion | Description |
| --- | --- |
| `ASSERT_THROW(statement, exception_type)` | Asserts statement to throw an exception of type `exception_type` |
| `ASSERT_ANY_THROW(statement)` | Asserts statement to throw any exception |

An unhandled exception during a test will fail that test and not terminate the testing suite.