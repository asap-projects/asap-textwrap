# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message("=> [third-party modules]")

# Live at Head philosophy. Always use the latest commit in the main branch in
# your projects.

# ------------------------------------------------------------------------------
# asap::common
# ------------------------------------------------------------------------------

FetchContent_Declare(
  asap_common
  GIT_REPOSITORY https://github.com/asap-projects/asap-common.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(asap_common)

# ------------------------------------------------------------------------------
# asap::fsm
# ------------------------------------------------------------------------------
set(ASAP_FSM_INSTALL ON)
FetchContent_Declare(
  asap_fsm
  GIT_REPOSITORY https://github.com/asap-projects/asap-fsm.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(asap_fsm)

# ------------------------------------------------------------------------------
# magic_enum
# ------------------------------------------------------------------------------

FetchContent_Declare(
  magic_enum
  GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(magic_enum)
