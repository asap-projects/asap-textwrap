//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include "tokenizer.h"

#include <type_traits>
#include <utility>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Eq;
using ::testing::IsTrue;

namespace asap::wrap::detail {

namespace {

// NOLINTNEXTLINE
TEST(TokenizerTest, Example) {
  //! [Tokenizer example]
  constexpr const char *tab = " ";
  constexpr bool collapse_ws = true;
  constexpr bool break_on_hyphens = true;

  const Tokenizer tokenizer{tab, collapse_ws, break_on_hyphens};

  constexpr const char *text = "Why? \nJust plain \tfinger-licking good!";
  std::vector<Token> tokens;
  const auto status = tokenizer.Tokenize(
      text, [&tokens](TokenType token_type, std::string token) {
        if (token_type != detail::TokenType::EndOfInput) {
          tokens.emplace_back(token_type, std::move(token));
        }
      });
  // All white spaces replaced and collapsed, hyphenated words
  // broken, to produce the following tokens:
  //     "Why?", " ", "Just", " ", "plain", " ",
  //     "finger-", "licking", " ", "good!"
  //! [Tokenizer example]

  const auto expected = std::vector<Token>{Token{TokenType::Chunk, "Why?"},
      Token{TokenType::WhiteSpace, " "}, Token{TokenType::NewLine, ""},
      Token{TokenType::Chunk, "Just"}, Token{TokenType::WhiteSpace, " "},
      Token{TokenType::Chunk, "plain"}, Token{TokenType::WhiteSpace, " "},
      Token{TokenType::Chunk, "finger-"}, Token{TokenType::Chunk, "licking"},
      Token{TokenType::WhiteSpace, " "}, Token{TokenType::Chunk, "good!"}};

  EXPECT_THAT(status, IsTrue());
  EXPECT_THAT(tokens.size(), Eq(expected.size()));
  auto expected_token = expected.cbegin();
  auto token = tokens.cbegin();
  const auto end = tokens.cend();
  while (token != end) {
    EXPECT_THAT(*token, Eq(*expected_token));
    ++token;
    ++expected_token;
  }
}

// NOLINTNEXTLINE
TEST(TokenizerTest, CallsTokenConsumerWhenTokenIsReady) {
  const Tokenizer tokenizer{"\t", false, false};

  //! [Example token consumer]
  std::vector<Token> tokens;
  const auto status = tokenizer.Tokenize(
      "Hello", [&tokens](TokenType token_type, std::string token) {
        if (token_type != detail::TokenType::EndOfInput) {
          tokens.emplace_back(token_type, std::move(token));
        }
      });
  //! [Example token consumer]

  EXPECT_THAT(status, IsTrue());
  EXPECT_THAT(tokens.size(), Eq(1));
  EXPECT_THAT(tokens, Eq(std::vector<Token>{Token{TokenType::Chunk, "Hello"}}));
}

using ParamType = std::tuple<
    // Input text
    std::string,
    // `tab` expansion
    std::string,
    // collapse white space
    bool,
    // break on hyphens
    bool,
    // expected tokens
    std::vector<Token>>;

class TokenizerScenariosTest : public ::testing::TestWithParam<ParamType> {};

// NOLINTNEXTLINE
TEST_P(TokenizerScenariosTest, Tokenize) {
  const auto &[text, tab, collapse_ws, break_on_hyphens, expected] = GetParam();
  const Tokenizer tokenizer{tab, collapse_ws, break_on_hyphens};

  std::vector<Token> tokens;
  const auto status = tokenizer.Tokenize(
      text, [&tokens](TokenType token_type, std::string token) {
        if (token_type != detail::TokenType::EndOfInput) {
          tokens.emplace_back(token_type, std::move(token));
        }
      });

  EXPECT_THAT(status, IsTrue());
  EXPECT_THAT(tokens.size(), Eq(expected.size()));
  auto expected_token = expected.cbegin();
  auto token = tokens.cbegin();
  const auto end = tokens.cend();
  while (token != end) {
    EXPECT_THAT(*token, Eq(*expected_token));
    ++token;
    ++expected_token;
  }
}

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(AllOff, TokenizerScenariosTest,
    // clang-format off
    testing::Values(
      ParamType{"",
        "\t", false, false,
        {
        }},
      ParamType{"\n",
        "\t", false, false,
        {
          {TokenType::NewLine, ""}
        }},
      ParamType{" \n",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, " "},
          {TokenType::NewLine, ""}
        }},
      ParamType{"\t\n",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, "\t"},
          {TokenType::NewLine, ""}
        }},
      ParamType{"\r\n",
        "\t", false, false,
        {
          {TokenType::NewLine, ""}
        }},
      ParamType{" \t\n",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, " \t"},
          {TokenType::NewLine, ""}
        }},
      ParamType{" \t\n ",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, " \t"},
          {TokenType::NewLine, ""},
          {TokenType::WhiteSpace, " "}
        }},
      ParamType{"\n\n",
        "\t", false, false,
        {
          {TokenType::ParagraphMark, ""}
        }},
      ParamType{" \n\n",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, " "},
          {TokenType::ParagraphMark, ""}
        }},
      ParamType{" \t\n \n\n \t\n \n",
        "\t", false, false,
        {
          {TokenType::WhiteSpace, " \t"},
          {TokenType::NewLine, ""},
          {TokenType::WhiteSpace, " "},
          {TokenType::ParagraphMark, ""},
          {TokenType::WhiteSpace, " \t"},
          {TokenType::NewLine, ""},
          {TokenType::WhiteSpace, " "},
          {TokenType::NewLine, ""}
        }},
      ParamType{"\n\n\n",
        "\t", false, false,
        {
          {TokenType::ParagraphMark, ""},
          {TokenType::NewLine, ""},
        }},
      ParamType{"\n\n\n\n",
        "\t", false, false,
        {
          {TokenType::ParagraphMark, ""},
          {TokenType::ParagraphMark, ""}
        }},
      ParamType{"very-very-long-word",
        "\t", false, false,
        {
          {TokenType::Chunk, "very-very-long-word"}
        }},
      ParamType{"Items\n\n1.\ta-a-a\n\n\n2.\tbbb or ccc",
        "\t", false, false,
        {
          {TokenType::Chunk, "Items"},
          {TokenType::ParagraphMark, ""},
          {TokenType::Chunk, "1."},
          {TokenType::WhiteSpace, "\t"},
          {TokenType::Chunk, "a-a-a"},
          {TokenType::ParagraphMark, ""},
          {TokenType::NewLine, ""},
          {TokenType::Chunk, "2."},
          {TokenType::WhiteSpace, "\t"},
          {TokenType::Chunk, "bbb"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "or"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "ccc"}
        }}
    )
);

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(TabExpansionOn, TokenizerScenariosTest,
    // clang-format off
    testing::Values(
      ParamType{"\t", "    ", false, false,
        {{TokenType::WhiteSpace, "    "}}},
      ParamType{"\t\taaa \t \tbbb", "__", false, false,
        {
          {TokenType::Chunk, "____aaa"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "__"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "__bbb"}
        }}
    )
);

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(CollapseWhiteSpaceOn, TokenizerScenariosTest,
    // clang-format off
    testing::Values(
      ParamType{"\t",
        "\t", true, false,
        {{TokenType::WhiteSpace, " "}}},
      ParamType{"\t",
        "  ", true, false,
        {{TokenType::WhiteSpace, " "}}},
      ParamType{"\t",
        "....", true, false,
        {{TokenType::Chunk, "...."}}},
      ParamType{"\t",
        "-\n-", true, false,
        {
          {TokenType::Chunk, "-"},
          {TokenType::NewLine, ""},
          {TokenType::Chunk, "-"}
        }},
      ParamType{"hello\f   world!\n\nbye\t\rbye \ncruel\v \t world! \r\n ",
        "..", true, false,
        {
          {TokenType::Chunk, "hello"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "world!"},
          {TokenType::ParagraphMark, ""},
          {TokenType::Chunk, "bye..bye"},
          {TokenType::WhiteSpace, " "},
          {TokenType::NewLine, ""},
          {TokenType::Chunk, "cruel"},
          {TokenType::NewLine, ""},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, ".."},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "world!"},
          {TokenType::WhiteSpace, " "},
          {TokenType::NewLine, ""},
          {TokenType::WhiteSpace, " "}
        }}
    )
);

// NOLINTNEXTLINE
INSTANTIATE_TEST_SUITE_P(BreakOnHyphensOn, TokenizerScenariosTest,
    // clang-format off
    testing::Values(
      ParamType{"a-b",
        "  ", false, true,
        {
          {TokenType::Chunk, "a-"},
          {TokenType::Chunk, "b"}
        }},
      ParamType{"universally-true",
        "  ", false, true,
        {
          {TokenType::Chunk, "universally-"},
          {TokenType::Chunk, "true"}
        }},
      ParamType{"some things-never-change",
        "  ", false, true,
        {
          {TokenType::Chunk, "some"},
          {TokenType::WhiteSpace, " "},
          {TokenType::Chunk, "things-"},
          {TokenType::Chunk, "never-"},
          {TokenType::Chunk, "change"}
        }},
      ParamType{"a-",
        "  ", false, true,
        {
          {TokenType::Chunk, "a-"}
        }},
      ParamType{"a--",
        "  ", false, true,
        {
          {TokenType::Chunk, "a-"},
          {TokenType::Chunk, "-"}
        }},
      ParamType{"--",
        "  ", false, true,
        {
          {TokenType::Chunk, "--"}
        }},
      ParamType{"---",
        "  ", false, true,
        {
          {TokenType::Chunk, "---"}
        }},
      ParamType{"-a-b-c---d-ef",
        "  ", false, true,
        {
          {TokenType::Chunk, "-a-"},
          {TokenType::Chunk, "b-"},
          {TokenType::Chunk, "c-"},
          {TokenType::Chunk, "--d-"},
          {TokenType::Chunk, "ef"}
        }}
    )
);

} // namespace

} // namespace asap::wrap::detail
