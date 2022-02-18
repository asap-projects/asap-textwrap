# C++ text wrapper and column formatter

![Start Now!!](doc/_static/logo.png "ASAP Logo")

[![Linux Build (Ubuntu latest)](https://github.com/asap-projects/asap-textwrap/actions/workflows/linux-build.yml/badge.svg?branch=master)](https://github.com/asap-projects/asap-textwrap/actions/workflows/linux-build.yml)
[![Windows Build (latest)](https://github.com/asap-projects/asap-textwrap/actions/workflows/windows-build.yml/badge.svg?branch=master)](https://github.com/asap-projects/asap-textwrap/actions/workflows/windows-build.yml)

## [Project Documentation](https://asap-projects.github.io/asap-textwrap/master/html/)

## Overview

This is a C++ library to format text in columns with a maximum width. When a
line of text is longer than its column's maximum width, the text is
automatically wrapped. A number of other features are also supported, such as
adding an initial indent, indenting all lines, etc... Refer to the API
documentation for more details.

Text can also be laid out by composing columns together in a multi-column
layout, suitable for tabular data, definitions, etc.

## Getting the code

```bash
git clone --recurse-submodules -j4 https://github.com/asap-projects/asap-textwrap.git
```

NOTES:

- -j4 requests git to parallelize cloning of repos. Needs a relatively recent
  version of git. If that is not available, simply do not use this option.

## Requirements

Make sure you have a C++ compiler with C++-17 capabilities at least. Gnu, Clang
and MSVC all can do that with a recent version.

## Building

```bash
mkdir _build && cd _build && cmake .. && cmake --build .
```

or just use one of the predefined `CMake` presets. Detailed instructions are in
the project documentation, and many useful commands are listed
[here](https://abdes.github.io/asap/master/html/getting-started/useful-commands.html).

## CMake configurable build options

```cmake
# Project options
option(BUILD_SHARED_LIBS        "Build shared instead of static libraries."              ON)
option(ASAP_BUILD_TESTS         "Build tests."                                           OFF)
option(ASAP_BUILD_EXAMPLES      "Build examples."                                        OFF)
option(ASAP_WITH_GOOGLE_ASAN    "Instrument code with address sanitizer"                 OFF)
option(ASAP_WITH_GOOGLE_UBSAN   "Instrument code with undefined behavior sanitizer"      OFF)
option(ASAP_WITH_GOOGLE_TSAN    "Instrument code with thread sanitizer"                  OFF)
option(ASAP_WITH_VALGRIND       "Builds targets with valgrind profilers added"           OFF)
```

## Making changes to this project

Read the developer guides in the upstream
[asap](https://abdes.github.io/asap/master/html/)
project. If you're in a hurry, at least do the following:

Only one time after the project is cloned, do the following:

```bash
npx husky install
npm install -g @commitlint/cli @commitlint/config-conventional
npm install -g standard-version
```
