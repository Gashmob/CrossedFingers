# Specifications

### Usage for testing:

```c++
// Calcul.hpp

class Calcul
{
public:
    int add(int a, int b)
    {
        return a + b;
    }
};

// CalculTest.cpp

#include "calcul.hpp"
#include <crossedfingers/test.h>

describe("Calcul", []() {
    Calcul calcul;
    
    before([]() {});
    beforeEach([]() {});
    
    after([]() {});
    afterEach([]() {});
    
    it("should can add two numbers", [&calcul]() {
        assertEquals(3, calcul.add(1, 2));
    });
    
    it_each({
        {1, 2, 3},
        {4, 5, 9},
        {10, 11, 21},
    }, "should do {} + {} = {}", [&calcul](int a, int b, int result) {
        assertEquals(result, calcul.add(a, b));
    });
});

beforeAll([]() {});
afterAll([]() {});
```

For all `assert*`, there is the same set as in phpunit.

`it_each` takes a `std::format` string.

### Usage in cmake:

```cmake
FetchContent_Declare(
        crossedfingers
        GIT_REPOSITORY https://github.com/Gashmob/CrossedFingers.git
        GIT_TAG v1.0.0
)
FetchContent_GetProperties(crossedfingers)

if (NOT crossedfingers_POPULATED)
    message(STATUS "Fetching CrossedFingers 🤞...")
    FetchContent_Populate(crossedfingers)
    add_subdirectory(${crossfingers_SOURCE_DIR})
endif ()

crossedfingers_collect_tests_files("tests/" tests_files)

add_executable(unit-tests ${tests_files})
target_link_libraries(unit-tests PUBLIC crossedfingers)

crossedfingers_discover_tests(unit-tests)
```

```bash
unit-tests run --filter 'Calcul.*' --export "xml" --output "results.xml"
unit-tests list
```
