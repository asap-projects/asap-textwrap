# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

# ==============================================================================
# Build instructions
# ==============================================================================

set(MAIN_TEST_TARGET_NAME ${MODULE_TARGET_NAME}_random_test)

asap_add_test(${MAIN_TEST_TARGET_NAME} INTEGRATION_TEST SRCS
              "textwrapper_random_test.cpp")
target_link_libraries(${MAIN_TEST_TARGET_NAME} PRIVATE asap::common
                                                       asap::textwrap)

# Add support for (optional) code quality tools
asap_add_sanitizers(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_massif(${MAIN_TEST_TARGET_NAME})
swift_add_valgrind_callgrind(${MAIN_TEST_TARGET_NAME})

# ------------------------------------------------------------------------------
# Run executable test as part of CTest
# ------------------------------------------------------------------------------

if(ASAP_BUILD_TESTS)
  add_test(
    NAME ${MAIN_TEST_TARGET_NAME}
    COMMAND ${MAIN_TEST_TARGET_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
endif()
