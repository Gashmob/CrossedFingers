include(CrossedFingers)

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# Unit tests

file(GLOB_RECURSE UNIT_TEST_FILES
        "${PROJECT_SOURCE_DIR}/tests/unit/*.cpp"
        "${PROJECT_SOURCE_DIR}/tests/unit/**/*.cpp"
        "${PROJECT_SOURCE_DIR}/tests/unit/*.h"
        "${PROJECT_SOURCE_DIR}/tests/unit/**/*.h"
)
message(DEBUG UNIT_TEST_FILES=${UNIT_TEST_FILES})

add_executable(unit-tests ${UNIT_TEST_FILES})
target_include_directories(unit-tests PUBLIC "${PROJECT_SOURCE_DIR}/tests/unit")
target_compile_definitions(unit-tests PUBLIC FIXTURES_PATH="${PROJECT_SOURCE_DIR}/tests/unit/Fixtures")

target_link_libraries(unit-tests PRIVATE crossedfingers crossedfingers_main)

crossedfingers_discover_tests(unit-tests
        PROPERTIES LABELS "unit"
)

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# Run tests

add_executable(run-tests "${PROJECT_SOURCE_DIR}/tests/run/test_run.test.cpp")
target_link_libraries(run-tests PRIVATE crossedfingers crossedfingers_main)

add_test(NAME run-tests COMMAND "run-tests")
set_tests_properties(run-tests PROPERTIES LABELS "unit")

# _.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-._.-.
# e2e tests

file(GLOB_RECURSE E2E_TEST_FILES
        "${PROJECT_SOURCE_DIR}/tests/e2e/*.cpp"
        "${PROJECT_SOURCE_DIR}/tests/e2e/**/*.cpp"
        "${PROJECT_SOURCE_DIR}/tests/e2e/*.h"
        "${PROJECT_SOURCE_DIR}/tests/e2e/**/*.h"
)
message(DEBUG E2E_TEST_FILES=${E2E_TEST_FILES})

add_executable(e2e-tests ${E2E_TEST_FILES})
add_dependencies(e2e-tests unit-tests)
target_include_directories(e2e-tests PUBLIC "${PROJECT_SOURCE_DIR}/tests/e2e")
target_compile_definitions(e2e-tests PUBLIC
        UNIT_TEST_BIN="$<TARGET_FILE:unit-tests>"
        FIXTURES_PATH="${PROJECT_SOURCE_DIR}/tests/e2e/Fixtures"
)

target_link_libraries(e2e-tests PRIVATE crossedfingers crossedfingers_main)

crossedfingers_discover_tests(e2e-tests
        PROPERTIES LABELS "e2e"
)
