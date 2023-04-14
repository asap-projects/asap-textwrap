# ===-----------------------------------------------------------------------===#
# Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
# copy at https://opensource.org/licenses/BSD-3-Clause).
# SPDX-License-Identifier: BSD-3-Clause
# ===-----------------------------------------------------------------------===#

# ==============================================================================
# Build instructions
# ==============================================================================

asap_add_executable("typical-example" WARNING SOURCES "typical_example.cpp")
target_link_libraries("typical-example" PRIVATE asap::textwrap)
