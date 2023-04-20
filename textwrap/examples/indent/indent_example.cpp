//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <textwrap/textwrap.h>

#include <iomanip>
#include <iostream>
#include <sstream>

using asap::wrap::TextWrapper;

auto main(int /*argc*/, const char ** /*argv*/) -> int {
  const auto *term = "gorgeous [ gawr-juhs ]\n\nadjective";
  const std::vector<std::string> definitions{
      "splendid or sumptuous in appearance, coloring, etc.; magnificent: a "
      "gorgeous gown; a gorgeous sunset.",
      "Informal. extremely good, enjoyable, or pleasant: I had a gorgeous "
      "time."};

  constexpr size_t column_width = 60;
  const TextWrapper term_wrapper =
      asap::wrap::MakeWrapper().Width(column_width).TrimLines();

  std::cout << term_wrapper.Fill(term).value_or("error") << std::endl;

  for (std::vector<std::string>::size_type index = 0;
       index < definitions.size(); index++) {

    constexpr auto prefix_width = 6;
    std::ostringstream first_line_prefix;
    first_line_prefix << std::setw(prefix_width - 2) << std::right << index
                      << "  ";
    std::string other_lines_prefix(prefix_width, ' ');
    TextWrapper definition_wrapper = asap::wrap::MakeWrapper()
                                         .Width(column_width)
                                         .TrimLines()
                                         .IndentWith()
                                         .Initially(first_line_prefix.str())
                                         .Then(other_lines_prefix);

    std::cout << definition_wrapper.Fill(definitions[index]).value_or("error")
              << "\n\n";
  }
}

// gorgeous [ gawr-juhs ]
//
// adjective
//    0  splendid or sumptuous in appearance, coloring, etc.;
//       magnificent: a gorgeous gown; a gorgeous sunset.
//
//    1  Informal. extremely good, enjoyable, or pleasant: I
//       had a gorgeous time.
