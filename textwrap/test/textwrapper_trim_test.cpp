//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "textwrap/textwrap.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;

namespace asap::wrap {

namespace {

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, NoSpaces) {
  constexpr size_t column_width = 30;
  const auto *text = "text";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("text"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesInTheMiddle) {
  constexpr size_t column_width = 30;
  const auto *text = "text with spaces inside";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("text with spaces inside"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesAtStart) {
  constexpr size_t column_width = 30;
  const auto *text = "   spaces_at_start";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("spaces_at_start"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesAtEnd) {
  constexpr size_t column_width = 5;
  const auto *text = "spaces_at_end   ";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("spaces_at_end"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, ManySpacesAtEndTrimmed) {
  constexpr size_t column_width = 5;
  const auto *text = "spaces_at_end            ";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("spaces_at_end"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesAtEveryWhere) {
  constexpr size_t column_width = 30;
  const auto *text = "    spaces\t\teverywhere \f\t   ";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("spaces\t\teverywhere"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, OnlySpaces) {
  constexpr size_t column_width = 30;
  const auto *text = "    \t \f\t   ";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq(""));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesBeforeNewLine) {
  constexpr size_t column_width = 30;
  const auto *text = "first   \nsecond";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("first\nsecond"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesAfterNewLine) {
  constexpr size_t column_width = 30;
  const auto *text = "first\n   second";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("first\nsecond"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, SpacesAroundNewLine) {
  constexpr size_t column_width = 4;
  const auto *text = "first   \n   second";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("first\nsecond"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, MultipleLines) {
  constexpr size_t column_width = 10;
  const auto *text = "first   \n   second   \n   third";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("first\nsecond\nthird"));
}

// NOLINTNEXTLINE
TEST(TextWrapperTrimLinesTest, OnlySpacesMultipleLines) {
  constexpr size_t column_width = 30;
  const auto *text = "\t  \n   \f \n    ";
  const TextWrapper wrapper =
      TextWrapper::Create().Width(column_width).TrimLines();
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("\n\n"));
}

} // namespace

} // namespace asap::wrap
