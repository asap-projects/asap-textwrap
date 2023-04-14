//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "textwrap/textwrap.h"

#include <cstring>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;

namespace asap::wrap {

namespace {

// NOLINTNEXTLINE
TEST(TextWrapperTest, ShortString) {
  constexpr size_t column_width = 30;
  const auto *text = "short string";
  const TextWrapper wrapper = TextWrapper::Create().Width(column_width);
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("short string"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTest, ExactString) {
  const auto *text = "short string";
  const size_t column_width = std::strlen(text);
  const TextWrapper wrapper = TextWrapper::Create().Width(column_width);
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("short string"));
}

using LongStringTestParamType = std::tuple<
    // width
    size_t,
    // replace white space
    bool,
    // Initial indent
    std::string,
    // Subsequent indents
    std::string,
    // expected result
    std::string>;

class LongStringTest
    : public ::testing::TestWithParam<LongStringTestParamType> {
public:
  inline static constexpr const char *text =
      "The quick brown fox jumped over the lazy dog";
};

// NOLINTNEXTLINE
TEST_P(LongStringTest, Fill) {
  const auto &[width, trim_lines, initial_indent, subsequent_indents,
      expected] = GetParam();
  auto builder = TextWrapper::Create();
  builder.Width(width);
  if (trim_lines) {
    builder.TrimLines();
  }
  builder.IndentWith().Initially(initial_indent).Then(subsequent_indents);
  const TextWrapper wrapper = builder;
  EXPECT_THAT(wrapper.Fill(text).value(), Eq(expected));
}

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(TrimLines, LongStringTest,
    // clang-format off
    testing::Values(
      LongStringTestParamType{7, true, "", "",
        "The\n"
        "quick\n"
        "brown\n"
        "fox\n"
        "jumped\n"
        "over\n"
        "the\n"
        "lazy\n"
        "dog"
      },
      LongStringTestParamType{8, true, "", "",
        "The\n"
        "quick\n"
        "brown\n"
        "fox\n"
        "jumped\n"
        "over the\n"
        "lazy dog"
      },
      LongStringTestParamType{9, true, "", "",
        "The quick\n"
        "brown fox\n"
        "jumped\n"
        "over the\n"
        "lazy dog"
      },
      LongStringTestParamType{10, true, "", "",
        "The quick\n"
        "brown fox\n"
        "jumped\n"
        "over the\n"
        "lazy dog"
      },
      LongStringTestParamType{11, true, "", "",
        "The quick\n"
        "brown fox\n"
        "jumped over\n"
        "the lazy\n"
        "dog"
      },
      LongStringTestParamType{12, true, "", "",
        "The quick\n"
        "brown fox\n"
        "jumped over\n"
        "the lazy dog"
      },
      LongStringTestParamType{20, true, "", "",
        "The quick brown fox\n"
        "jumped over the lazy\n"
        "dog"
      }
    ) //  clang-format on
);

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(NoTrimLines, LongStringTest,
    // clang-format off
    testing::Values(
      LongStringTestParamType{7, false, "", "",
        "The \n"
        "quick\n"
        " brown\n"
        " fox \n"
        "jumped\n"
        " over\n"
        " the \n"
        "lazy \n"
        "dog"
      },
      LongStringTestParamType{10, false, "", "",
        "The quick\n"
        " brown fox\n"
        " jumped \n"
        "over the \n"
        "lazy dog"
      },
      LongStringTestParamType{20, false, "", "",
        "The quick brown fox \n"
        "jumped over the lazy\n"
        " dog"
      }
    ) // clang-format on
);

} // namespace

} // namespace asap::wrap
