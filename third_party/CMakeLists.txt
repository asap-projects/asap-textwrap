# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

message("=> [third-party modules]")

# ------------------------------------------------------------------------------
# gsl
# ------------------------------------------------------------------------------

set(GSL_INSTALL ON)
add_subdirectory(gsl)

# ------------------------------------------------------------------------------
# magic_enum
# ------------------------------------------------------------------------------

set(MAGIC_ENUM_OPT_INSTALL TRUE)
add_subdirectory(magic_enum)

# ------------------------------------------------------------------------------
# fmt (must come before spdlog)
# ------------------------------------------------------------------------------

# We want the spdlog install target to be generated even though we are using it
# as a submodule. The reason for that is that is spdlog and also we want our
# project to be self contained with all dependencies included.
set(FMT_INSTALL
    ON
    CACHE BOOL "Generate the install target.")

add_subdirectory(fmt)
