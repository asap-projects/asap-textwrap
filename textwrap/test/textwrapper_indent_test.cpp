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
TEST(TextWrapperIndentTest, IndentInitialOnly) {
  constexpr size_t column_width = 6;
  const auto *text = "hello world!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("--- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("--- hello\nworld!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentNoInitial) {
  constexpr size_t column_width = 6;
  const auto *text = "hello world!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("")
                                  .Then("--- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("hello\n--- world!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentAll) {
  constexpr size_t column_width = 6;
  const auto *text = "hello world!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("== hello\n---- world!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentOneWord) {
  constexpr size_t column_width = 3;
  const auto *text = "hello";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("== hello"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentExactWidth) {
  constexpr size_t column_width = 17;
  const auto *text = "hello world!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("==== hello world!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentMultipleLines) {
  constexpr size_t column_width = 10;
  const auto *text = "bye world - welcome universe!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .TrimLines()
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("==== bye\n"
                                             "---- world\n"
                                             "---- -\n"
                                             "---- welcome\n"
                                             "---- universe!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentEmptyStringNotIndented) {
  constexpr size_t column_width = 17;
  const auto *text = "";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq(""));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentEmptyLineNotIndented) {
  constexpr size_t column_width = 17;
  const auto *text = "\nworld!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("==== \n---- world!"));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentOnlyNewLineProducesTwoIndentedLines) {
  constexpr size_t column_width = 17;
  const auto *text = "\n";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("==== "));
}

// NOLINTNEXTLINE
TEST(TextWrapperIndentTest, IndentNewLineIsIndented) {
  constexpr size_t column_width = 17;
  const auto *text = "hello\nworld!";
  const TextWrapper wrapper = TextWrapper::Create()
                                  .Width(column_width)
                                  .IndentWith()
                                  .Initially("==== ")
                                  .Then("---- ");
  EXPECT_THAT(wrapper.Fill(text).value(), Eq("==== hello\n---- world!"));
}

} // namespace

} // namespace asap::wrap
