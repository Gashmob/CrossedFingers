# Usage documentation

> [!tip]
> This library needs at least c++23 features.

This library is heavily inspired by jest/vitest/pest and equivalent.

The first thing to do is include `crossedfingers/test.h` header. It contains all you need to write tests. Let's
decompose it.

When you write tests, you describe the behavior of something, thus the name of the first function (in fact, it is a
macro): `describe`. It takes two arguments, the identifier of what you describe and a lambda.

```cpp
#include <crossedfingers/test.h>

// Here we will describe Addition class behavior
describe(Addition, []() {
    // You can of course have nested describe
    describe(compute, []() {});
});
```

Be careful with the identifier, it must be a valid C++ identifier.

Then you can begin to write test cases with `it`. It also takes two arguments, the test name (a std::string) and a
lambda.

```cpp
#include <crossedfingers/test.h>

describe(Addition, []() {
    it("Should do 1 + 1 and return 2", []() {});
});
```

And finally you can write assertions with `assertThat`.

```cpp
#include <crossedfingers/test.h>

describe(Addition, []() {
    it("Should do 1 + 1 and return 2", []() {
        assertThat(1 + 1).isEqualTo(2);
    });
});
```

Congratulations, you have written your first test with CrossedFingers 🤞. In next steps we'll dive further in what you
can do.

## Assertions

All assertions begin with a call to `assertThat`. It takes only one argument → the thing you will assert on. It returns
an object on which you can call many methods to check it. Here we will see the full list of these methods.

All the following methods are under `crossedfingers::` namespace. To shorten code snippets and ease the read, we'll
assume that we have called `using namespace crossedfingers;`.

### `isTrue()`

Check that value is equal to `true`.

### `isFalse()`

Check that value is equal to `false`.

### `isEqualTo(expected)`

Check that value is equal to `expected`.

### `isStrictEqualTo(expected)`

Check that value has the same type and is equal to `expected`.

### `isNotEqualTo(expected)`

Check that value is not equal to `expected`.

### `isLessThan(expected)`

Check that value is less than `expected`.

### `isLessThanOrEqualTo(expected)`

Check that value is less than or equal to `expected`.

### `isGreaterThan(expected)`

Check that value is greater than `expected`.

### `isGreaterThanOrEqualTo(expected)`

Check that value is greater than or equal to `expected`.

### `matchesRegex(pattern)`

Only available if assertThat was called with a std::string.

Check that value matches `pattern`.

### `hasSubString(sub)`

Only available if assertThat was called with a std::string.

Check that value contains `sub`.

### `startsWith(start)`

Only available if assertThat was called with a std::string.

Check that value starts with `start`.

### `endsWith(end)`

Only available if assertThat was called with a std::string.

Check that value ends with `end`.

### `contains(expected)`

Only available if assertThat was called with a container.

Check that container contains `expected`.

### `hasKey(key)`

Only available if assertThat was called with a std::map.

Check that map has key `key`.

### `count(number)`

Only available if assertThat was called with a container.

Check that container has `number` elements.

### `isEmpty()`

Only available if assertThat was called with a container.

Check that container has no elements.

### `matchPredicate(predicate)`

`predicate` is a function taking one argument and returning a boolean. The argument type must be compatible with the
value passed to assertThat.

Check that `predicate` called with value returns true.

### `matchType<Type>()`

Check that value is of type `Type`.

### `isNull()`

Check that value is equal to `nullptr`.

### `isFile()`

Only available if assertThat was called with a std::string.

Check that value is a path to an existing file.

### `isDirectory()`

Only available if assertThat was called with a std::string.

Check that value is a path to an existing directory.

The first sentence of this section was a lie, as there is one assertion you cannot do with assertThat, exceptions. For
this unique case, you first declare that you except an exception to be thrown and then call the throwing expression.

```cpp
expectException<std::logic_error>();
throwingMethod();
```

## Parameterized tests

```cpp
// Instead of writing
it("Should do 1 + 1 and return 2", []() {
    assertThat(1 + 1).isEqualTo(2);
});

it("Should do 2 + 2 and return 4", []() {
    assertThat(2 + 2).isEqualTo(4);
});

// You can write
it_each<void(int, int, int), int, int, int>(
    {
        {1, 1, 2},
        {2, 2, 4},
    },
    "Should do {} + {} and return {}",
    [](int lo, int ro, int result) {
        assertThat(lo + ro).isEqualTo(result);
    }
);
```

## Before and After

There are four methods that can be called with a lambda to add some behavior before and after your tests.

### `before(lambda)`

Is called at the start of the test suite.

### `beforeEach(lambda)`

Is called before each test case.

### `afterEach(lambda)`

Is called after each test case.

### `after(lambda)`

Is called at the end of the test suite.

## CMake notice

If you use CMake to set up your tests. Please take a look at this snippet for how you can declare tests.

```cmake
# You first declare an executable as always
add_executable(unit-tests ...)

# Then you link crossedfingers crossedfingers_main libraries
target_link_libraries(unit-tests PRIVATE crossedfingers crossedfingers_main)

# This function list all test cases for ctest
crossedfingers_discover_tests(unit-tests)
```

`crossedfingers_main` is a small library containing just the `main` function. It is in a separate library in case you
want to write your own main. For reference, the main actually looks like this:

```cpp
#include <crossedfingers/test.h>

auto main(int argc, char **argv) -> int {
    return crossedfingers::internals::TestRun::instance().run(argc, argv);
}
```

> [!tip]
> If anything is unclear, if you have remarks, you are welcome to open an issue in the GitHub repository.
