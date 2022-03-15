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

cpmaddpackage(NAME asap_common GIT_TAG v2.0.4 GITHUB_REPOSITORY
              asap-projects/asap-common)

# ------------------------------------------------------------------------------
# asap::fsm
# ------------------------------------------------------------------------------

cpmaddpackage(
  NAME
  asap_fsm
  GIT_TAG
  v1.0.5
  GITHUB_REPOSITORY
  asap-projects/asap-fsm
  OPTIONS
  "ASAP_FSM_INSTALL ON")

# ------------------------------------------------------------------------------
# magic_enum
# ------------------------------------------------------------------------------

cpmaddpackage(NAME magic_enum GIT_TAG master GITHUB_REPOSITORY
              Neargye/magic_enum)
