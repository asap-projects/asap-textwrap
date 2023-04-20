//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <textwrap/textwrap.h>

#include <array>
#include <chrono>
#include <iostream>
#include <random>

#include <common/compilers.h>

// Seed the random number generator with the current time
std::random_device rd;
std::mt19937 rng(rd());                // NOLINT
using rng_type = std::uniform_int_distribution<std::mt19937::result_type>;
rng_type word_char_generator(33, 126); // NOLINT
rng_type ws_generator(0, 11);          // NOLINT
rng_type word_size_generator(1, 10);   // NOLINT
rng_type ws_size_generator(1, 2);      // NOLINT
rng_type punct_generator(0, 4);        // NOLINT

auto RandomWordChar() -> char {
  return static_cast<char>(word_char_generator(rng));
}
auto RandomWhiteSpace() -> char {
  static constexpr auto white_space = std::array<const char, 14>{{' ', ' ', ' ',
      ' ', ' ', ' ', ' ', ' ', ' ', '\t', '\v', '\f', '\r', '\n'}};
  return (white_space.at(ws_generator(rng)));
}
auto GenerateWord(size_t length) -> std::string {
  std::string result;
  for (; length > 0; --length) {
    result += RandomWordChar();
  }
  return result;
}
auto GenerateWord() -> std::string {
  return GenerateWord(word_size_generator(rng));
}
auto GenerateWhiteSpace(size_t length) -> std::string {
  std::string result;
  for (; length > 0; --length) {
    result += RandomWhiteSpace();
  }
  return result;
}
auto GenerateText(size_t words) -> std::string {
  std::string text;
  for (; words > 0; --words) {
    text += GenerateWord();
    switch (punct_generator(rng)) {
    case 0:
      text += ";";
    case 1:
    case 2:
      text += ",";
      break;
    case 3:
    case 4:
      text += ".";
      break;
    default:
      ASAP_UNREACHABLE();
    }
    text += GenerateWhiteSpace(ws_size_generator(rng));
  }
  return text;
}

template <class DT = std::chrono::milliseconds,
    class ClockT = std::chrono::steady_clock>
class Timer {
  using timep_t = typename ClockT::time_point;
  timep_t _start = ClockT::now(), _end = {};

public:
  void tick() {
    _end = timep_t{};
    _start = ClockT::now();
  }

  void tock() {
    _end = ClockT::now();
  }

  template <class T = DT> [[nodiscard]] auto duration() const {
    return std::chrono::duration_cast<T>(_end - _start);
  }
};

std::string escape(const std::string &s) {
  std::string result;

  for (char c : s) {
    switch (c) {
    case '\\':
      result += "\\\\";
      break;
    case '\"':
      result += "\\\"";
      break;
    case '\'':
      result += "\\\'";
      break;
    case '\n':
      result += "\\n";
      break;
    case '\r':
      result += "\\r";
      break;
    case '\v':
      result += "\\v";
      break;
    case '\f':
      result += "\\f";
      break;
    case '\t':
      result += "\\t";
      break;
    // Add more cases here
    default:
      result += c;
      break;
    }
  }

  return result;
}

using asap::wrap::TextWrapper;

auto main(int /*argc*/, const char ** /*argv*/) -> int {
  constexpr size_t maximum_text_length = 80;

  Timer<std::chrono::milliseconds, std::chrono::steady_clock> clock;

  clock.tick();
  for (size_t i = 1; i < maximum_text_length; ++i) {
    auto text = GenerateText(i);
    const auto size = text.size();
    for (size_t column_width = 1; column_width < size; ++column_width) {
      const TextWrapper &text_wrapper = asap::wrap::MakeWrapper()
                                            .Width(column_width)
                                            .CollapseWhiteSpace()
                                            .BreakOnHyphens()
                                            .TrimLines();
      if (!text_wrapper.Fill(text).has_value()) {
        std::cout << "width=" << column_width << "\n";
        std::cout << escape(text) << "\n" << std::endl;
        std::cerr << "Failed!\n";
      }
    }
  }
  clock.tock();

  std::cout << "Run time = " << clock.duration().count() << " ms\n";
}
