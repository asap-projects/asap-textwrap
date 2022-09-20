# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message(STATUS "${ASAP_LOG_PROJECT_HIERARCHY} >> third-party modules")

# Call `asap_add_package` to add third party packages using CPM, while
# automatically adding/removing them to the project hierarchy stack.
#
# Refer to https://github.com/cpm-cmake/CPM.cmake for the full usage.
#
# Example:
# ~~~
# asap_add_package(
#   NAME
#   magic_enum
#   GIT_TAG
#   master
#   GITHUB_REPOSITORY
#   abdes/magic_enum
#   OPTIONS
#   "MAGIC_ENUM_OPT_INSTALL ON")
# ~~~

# Live at Head philosophy. Always use the latest commit in the main branch in
# your projects.

# ------------------------------------------------------------------------------
# asap::common
# ------------------------------------------------------------------------------

asap_add_package(
  NAME
  asap_common
  GIT_TAG
  master
  GITHUB_REPOSITORY
  asap-projects/asap-common
  OPTIONS
  "ASAP_COMMON_INSTALL OFF"
  "ASAP_BUILD_TESTS OFF"
  "ASAP_BUILD_EXAMPLES OFF")

# ------------------------------------------------------------------------------
# asap::fsm
# ------------------------------------------------------------------------------

asap_add_package(
  NAME
  asap_fsm
  GIT_TAG
  master
  GITHUB_REPOSITORY
  asap-projects/asap-fsm
  OPTIONS
  "ASAP_COMMON_INSTALL OFF"
  "ASAP_BUILD_TESTS OFF"
  "ASAP_BUILD_EXAMPLES OFF")

# ------------------------------------------------------------------------------
# magic_enum
# ------------------------------------------------------------------------------

asap_add_package(NAME magic_enum GIT_TAG master GITHUB_REPOSITORY
                 Neargye/magic_enum)
