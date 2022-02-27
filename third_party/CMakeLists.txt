# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message("=> [third-party modules]")

include(FetchContent)
# We make sure that we have 'third_party' in the name so that the targets get
# excluded from the generated target lists for the various tools.
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/third_party_deps)

include(FetchGoogleTest)

# Live at Head philosophy. Always use the latest commit in the main branch in
# your projects.

# ------------------------------------------------------------------------------
# asaP::common
# ------------------------------------------------------------------------------

FetchContent_Declare(
  asap_common
  GIT_REPOSITORY https://github.com/asap-projects/asap-common.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(asap_common)

# ------------------------------------------------------------------------------
# asap::fsm
# ------------------------------------------------------------------------------
set(ASAP_FSM_INSTALL OFF)
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

# ------------------------------------------------------------------------------
# fmt (must come before spdlog)
# ------------------------------------------------------------------------------

set(FMT_INSTALL ON)
FetchContent_Declare(
  fmtlib_fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG origin/master)
FetchContent_MakeAvailable(fmtlib_fmt)
