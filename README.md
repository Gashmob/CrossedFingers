# Crossed Fingers 🤞

[![License: MIT](https://img.shields.io/github/license/gashmob/crossedfingers)](https://opensource.org/licenses/MIT)
![Version](https://img.shields.io/github/v/release/gashmob/crossedfingers?include_prereleases)

C++ testing framework

## Installation

You can retrieve rpm/deb package attached
to [latest release](https://github.com/Gashmob/CrossedFingers/releases/latest).

Devel packages are also built for each push to master branch
in [package workflow](https://github.com/Gashmob/CrossedFingers/actions/workflows/package.yml?query=branch%3Amaster).

A nix flake package is also available inside [flake.nix](flake.nix).

For CMake-based projects, you can simply use `FetchContent` this way:

```cmake
FetchContent_Declare(
        crossedfingers
        GIT_REPOSITORY https://github.com/Gashmob/CrossedFingers.git
        GIT_TAG v1.0.0
)
FetchContent_GetProperties(crossedfingers)

if (NOT crossedfingers_POPULATED)
    message(STATUS "Fetching crossedfingers...")
    FetchContent_Populate(crossedfingers)
    add_subdirectory(${crossedfingers_SOURCE_DIR})
endif ()

target_link_libraries(my_test PUBLIC crossedfingers crossedfingers_main)
```

## Usage

See [USAGE.md](USAGE.md).

## Contributors

Want to contribute? Please read [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) and [CONTRIBUTING.md](CONTRIBUTING.md)

List of contributors *(ordered by date of first contribution)*
![GitHub contributors](https://img.shields.io/github/contributors/Gashmob/CrossedFingers)

- [Gashmob](https://github.com/Gashmob)

## Security

See [SECURITY.md](SECURITY.md).
