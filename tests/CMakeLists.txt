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
target_include_directories(unit-tests PUBLIC
        "${PROJECT_SOURCE_DIR}/tests/unit")
target_compile_definitions(unit-tests PUBLIC FIXTURES_PATH="${PROJECT_SOURCE_DIR}/tests/unit/Fixtures")

target_link_libraries(unit-tests PRIVATE crossed_fingers crossed_fingers_main)

add_test(NAME unit-tests COMMAND "unit-tests")
