# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

# ==============================================================================
# Build instructions
# ==============================================================================

set(MAIN_TEST_TARGET_NAME ${MODULE_TARGET_NAME}_test)

asap_add_test(
  ${MAIN_TEST_TARGET_NAME}
  UNIT_TEST
  VALGRIND_MEMCHECK
  SRCS
  "main.cpp"
  "textwrapper_example.cpp"
  "textwrapper_indent_test.cpp"
  "textwrapper_special_cases_test.cpp"
  "textwrapper_test.cpp"
  "textwrapper_trim_test.cpp"
  "tokenizer_test.cpp"
  LINK
  asap::common
  asap::textwrap
  gtest_main
  gmock_main
  COMMENT
  "ASAP textwrap unit tests")

target_include_directories(${MAIN_TEST_TARGET_NAME} PRIVATE "../src")

gtest_discover_tests(${MAIN_TEST_TARGET_NAME})

# Add support for (optional) code quality tools
asap_add_sanitizers(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_massif(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_callgrind(${MAIN_TEST_TARGET_NAME})

# ------------------------------------------------------------------------------
# Long-running random tests
# ------------------------------------------------------------------------------

add_subdirectory(fuzzing)
