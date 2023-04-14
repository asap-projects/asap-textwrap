# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

# ==============================================================================
# Build instructions
# ==============================================================================

asap_add_executable("spaces-example" WARNING SOURCES "spaces_example.cpp")
target_link_libraries("spaces-example" PRIVATE asap::textwrap)
