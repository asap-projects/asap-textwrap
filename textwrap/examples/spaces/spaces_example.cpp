//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <textwrap/textwrap.h>

#include <iostream>

using asap::wrap::TextWrapper;

auto main(int /*argc*/, const char ** /*argv*/) -> int {
  const auto *passage =
      "Miranda said:\n\t'It seems to me like the recollection of a dream.   "
      "But had I not once four or five women who attended upon "
      "me?'\n\nProspero answered:\n\t'You had, and more. How is it that this "
      "still lives in your mind?  Do you remember how you came here?'";

  constexpr size_t column_width = 70;
  const TextWrapper wrapper = asap::wrap::MakeWrapper()
                                  .Width(column_width)
                                  .ExpandTabs("")
                                  .CollapseWhiteSpace()
                                  .IndentWith()
                                  .Initially("")
                                  .Then(" > ");

  std::cout << wrapper.Fill(passage).value_or("error") << std::endl;
}

// Miranda said:
//  > 'It seems to me like the recollection of a dream. But had I not
//  > once four or five women who attended upon me?'
//
// Prospero answered:
//  > 'You had, and more. How is it that this still lives in your mind?
//  > Do you remember how you came here?'
