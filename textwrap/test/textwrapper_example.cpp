//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "textwrap/textwrap.h"

#include <gtest/gtest.h>

namespace asap::wrap {

namespace {

// NOLINTNEXTLINE
TEST(TextWrapperExamples, TypicalWrapWithLineBreaksAndCollapsedSpaces) {
  //! [Example usage]
  const auto *passage =
      "  Pride and Prejudice:\n    It is a truth universally   "
      "acknowledged, that a single man in possession of a "
      "good fortune, must be in want "
      "of a wife.   ";

  constexpr size_t column_width = 28;
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .ReplaceWhiteSpace()
                                  .CollapseWhiteSpace()
                                  .IndentWith()
                                  .Initially("")
                                  .Then("...");

  std::cout << "|" << wrapper.Fill(passage).value_or("error") << "|"
            << std::endl;

  // Pride and Prejudice:
  //    It is a truth universally
  //    acknowledged, that a single
  //    man in possession of a good
  //    fortune, must be in want of
  //    a wife.

  //! [Example usage]
}

} // namespace

} // namespace asap::wrap
