//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

/*!
 * \file
 *
 * \brief Implementation details of the text wrapper tokenizer.
 */

#include "tokenizer.h"

#include <algorithm>
#include <numeric>
#include <utility>

#include <magic_enum.hpp>

#include <fsm/fsm.h>

using asap::fsm::ByDefault;
using asap::fsm::Continue;
using asap::fsm::DoNothing;
using asap::fsm::On;
using asap::fsm::ReissueEvent;
using asap::fsm::StateMachine;
using asap::fsm::Status;
using asap::fsm::Terminate;
using asap::fsm::TerminateWithError;
using asap::fsm::TransitionTo;
using asap::fsm::Will;

using asap::wrap::detail::Token;
using asap::wrap::detail::TokenConsumer;
using asap::wrap::detail::TokenType;

// -----------------------------------------------------------------------------
//  TokenType formatting helpers
// -----------------------------------------------------------------------------

auto asap::wrap::detail::operator<<(
    std::ostream &out, const TokenType &token_type) -> std::ostream & {
  out << magic_enum::enum_name(token_type);
  return out;
}

// -----------------------------------------------------------------------------
//  Tokenizer state machine events
// -----------------------------------------------------------------------------

namespace {

struct NonWhiteSpaceChar {
  explicit NonWhiteSpaceChar(char character) : value{character} {
  }
  const char value;
};
struct WhiteSpaceChar {
  explicit WhiteSpaceChar(char character) : value{character} {
  }
  const char value;
};
struct InputEnd {};

} // namespace

// -----------------------------------------------------------------------------
//  Formatting helpers for the Tokenizer events
// -----------------------------------------------------------------------------

/*!
 * \brief Make a white space character safe for printing by adding a '\' if
 * needed.
 *
 * This function takes any character and if it is a special white space
 * character that needs escaping it transforms it into a safe string for
 * printing by adding a `\` in front of the character.
 *
 * Characters that get escaped are: `\n`, `\r`, `\f`, `\v`, `\t`.
 */
inline auto EscapeSpecialWhiteSpaces(const char &character) -> std::string {
  // Escape special white space characters
  std::string escaped;
  switch (character) {
  case '\n':
    escaped = "\\n";
    break;
  case '\f':
    escaped = "\\f";
    break;
  case '\r':
    escaped = "\\r";
    break;
  case '\t':
    escaped = "\\t";
    break;
  case '\v':
    escaped = "\\v";
    break;
  default:
    escaped = character;
  }
  return escaped;
}

/*!
 * \brief Make a string safe for printing by escaping any special white space
 * characters in it.
 *
 * \see EscapeSpecialWhiteSpaces
 */
inline auto EscapeSpecialWhiteSpaces(const std::string &str) -> std::string {
  return std::accumulate(
      str.cbegin(), str.cend(), std::string(), [](auto &dest, char value) {
        dest.append(EscapeSpecialWhiteSpaces(value));
        return dest;
      });
}

// -----------------------------------------------------------------------------
//  Tokenizer state machine states
// -----------------------------------------------------------------------------

namespace {

struct InitialState;
struct WordState;
struct WhiteSpaceState;
struct FinalState;

/*!
 * \brief Pass a token to a token consumer.
 *
 * This utility function passes the token to the token consumer and clears the
 * token before returning.
 */
void DispatchTokenToConsumer(const TokenConsumer &consume_token,
    TokenType token_type, std::string &token) {
  consume_token(token_type, token);
  token.clear();
}

/*!
 * \brief The final state of the tokenizer state machine.
 *
 * When the state machine enters this state, a final token event of type
 * TokenType::EndOfInput will be dispatched to the token consumer. After that,
 * the state machine is a completed execution state and no more tokens will be
 * produced. The tokenizer can be reused for a new input text.
 */
struct FinalState : public Will<ByDefault<DoNothing>> {
  explicit FinalState(TokenConsumer callback)
      : consume_token_{std::move(callback)} {
  }

  [[maybe_unused]] auto OnEnter(const InputEnd & /*event*/) -> Status {
    consume_token_(TokenType::EndOfInput, "");
    return Terminate{};
  }

private:
  TokenConsumer consume_token_;
};

/*!
 * \brief The initial state of the tokenizer state machine.
 *
 * This is the starting state of the tokenizer. Based on which first token will
 * be extracted from the input text, this state will transition to one of the
 * next states.
 */
struct InitialState
    : public Will<On<NonWhiteSpaceChar, TransitionTo<WordState>>,
          On<WhiteSpaceChar, TransitionTo<WhiteSpaceState>>,
          On<InputEnd, TransitionTo<FinalState>>> {
  using Will::Handle;
};

/*!
 * \brief Tokenizer state while forming a chunk of non-white-space text.
 *
 * In this state, the tokenizer accumulates input characters into a chunk until
 * it encounters a white space character, a hyphen when break_on_hyphens is
 * `true` or the end of input. At that moment, it dispatches the chunk as a
 * token to the token consumer and transitions to the next state corresponding
 * to the last event.
 */
struct WordState : public Will<On<InputEnd, TransitionTo<FinalState>>,
                       On<WhiteSpaceChar, TransitionTo<WhiteSpaceState>>> {
  using Will::Handle;

  WordState(TokenConsumer callback, bool break_on_hyphens)
      : consume_token_{std::move(callback)},
        break_on_hyphens_{break_on_hyphens} {
  }

  [[maybe_unused]] static auto OnEnter(const NonWhiteSpaceChar & /*event*/)
      -> Status {
    return ReissueEvent{};
  }

  template <typename Event> auto OnLeave(const Event & /*event*/) -> Status {
    if (!token_.empty()) {
      DispatchTokenToConsumer(consume_token_, TokenType::Chunk, token_);
    }
    return Continue{};
  }

  [[maybe_unused]] auto Handle(const NonWhiteSpaceChar &event) -> DoNothing {
    if (break_on_hyphens_ && event.value == '-' && !token_.empty() &&
        (std::isalpha(token_.back()) != 0)) {
      token_.push_back(event.value);
      DispatchTokenToConsumer(consume_token_, TokenType::Chunk, token_);
    } else {
      token_.push_back(event.value);
    }
    return DoNothing{};
  }

private:
  std::string token_;
  TokenConsumer consume_token_;
  const bool break_on_hyphens_;
};

/*!
 * \brief Tokenizer state while getting white-space as input characters.
 *
 * In this state, the tokenizer is waiting for a non-white-space to start
 * forming a new chunk or for the end of input to terminate. Any white space
 * characters are collected into a temporary token to be transformed as per the
 * configured parameters (see Tokenizer class description for a detailed
 * description of these parameters). The white space token is then dispatched to
 * the token consumer and the state machine transitions into the next state
 * based on the last event.
 */
struct WhiteSpaceState : public Will<On<InputEnd, TransitionTo<FinalState>>,
                             On<NonWhiteSpaceChar, TransitionTo<WordState>>> {
  using Will::Handle;

  explicit WhiteSpaceState(TokenConsumer callback, bool collapse_ws)
      : consume_token_{std::move(callback)}, collapse_ws_{collapse_ws} {
  }

  [[maybe_unused]] static auto OnEnter(const WhiteSpaceChar & /*event*/)
      -> Status {
    return ReissueEvent{};
  }

  template <typename Event> auto OnLeave(const Event & /*event*/) -> Status {
    if (!token_.empty()) {
      // This is not a paragraph mark so dispatch as white space or new line
      // token based on the last seen character
      if (last_was_newline_) {
        token_.pop_back();
        if (!token_.empty()) {
          DispatchToConsumer(TokenType::WhiteSpace);
        }
        DispatchToConsumer(TokenType::NewLine);
      } else {
        DispatchToConsumer(TokenType::WhiteSpace);
      }
    }
    last_was_newline_ = false;
    return Continue{};
  }

  [[maybe_unused]] auto Handle(const WhiteSpaceChar &event) -> DoNothing {
    if (event.value == '\n' || event.value == '\v') {
      if (last_was_newline_) {
        token_.pop_back();
        if (!token_.empty()) {
          DispatchToConsumer(TokenType::WhiteSpace);
        }
        DispatchToConsumer(TokenType::ParagraphMark);
        token_ = "";
        last_was_newline_ = false;
        return DoNothing{};
      }
      last_was_newline_ = true;
      token_.push_back('\n');
    } else {
      if (last_was_newline_) {
        last_was_newline_ = false;
        token_.pop_back();
        if (!token_.empty()) {
          DispatchToConsumer(TokenType::WhiteSpace);
        }
        DispatchToConsumer(TokenType::NewLine);
      }
      token_.push_back(event.value);
    }
    return DoNothing{};
  }

private:
  void DispatchToConsumer(TokenType token_type) {
    // If the token is a white space, and we need to collapse white spaces, do
    // it now.
    if (token_type == TokenType::WhiteSpace) {
      if (collapse_ws_) {
        token_ = " ";
      }
      DispatchTokenToConsumer(consume_token_, TokenType::WhiteSpace, token_);
    } else {
      DispatchTokenToConsumer(consume_token_, token_type, token_);
    }
  }

  bool last_was_newline_{false};
  std::string token_;
  TokenConsumer consume_token_;
  const bool collapse_ws_;
};

} // namespace

/*!
 * \brief The Overload pattern allows to explicitly 'overload' lambdas and is
 * particularly useful for creating visitors, e.g. for std::variant.
 */
template <typename... Ts> // (7)
struct Overload : Ts... {
  using Ts::operator()...;
};
// Deduction guide only needed for C++17. C++20 can automatically create the
// template parameters out of the constructor arguments.
template <class... Ts> Overload(Ts...) -> Overload<Ts...>;

auto asap::wrap::detail::Tokenizer::Tokenize(
    const std::string &text, const TokenConsumer &consume_token) const -> bool {

  using Machine =
      StateMachine<InitialState, WordState, WhiteSpaceState, FinalState>;
  Machine machine{InitialState(), WordState(consume_token, break_on_hyphens_),
      WhiteSpaceState(consume_token, collapse_ws_), FinalState(consume_token)};

  bool continue_running{true};
  bool no_errors{true};
  bool reissue = false;

  auto cursor = text.begin();
  while (cursor != text.end()) {
    // '\r' amd '\f' are mot helpful or useful in proper formatting of the
    // wrapped text. They are simply ignored.
    if (*cursor == '\r' || *cursor == '\f') {
      ++cursor;
      continue;
    }

    Status execution_status;

    std::string transformed{(*cursor)};
    // Expand tabs
    if (*cursor == '\t') {
      transformed = tab_;
    }

    auto transformed_cursor = transformed.begin();
    while (transformed_cursor != transformed.end()) {

      if (std::isspace(*transformed_cursor) != 0) {
        execution_status = machine.Handle(WhiteSpaceChar{*transformed_cursor});
      } else {
        execution_status =
            machine.Handle(NonWhiteSpaceChar{*transformed_cursor});
      }
      // https://en.cppreference.com/w/cpp/utility/variant/visit
      std::visit(
          Overload{
              [&continue_running](const Continue & /*status*/) noexcept {
                continue_running = true;
              },
              [&continue_running](const Terminate & /*status*/) noexcept {
                continue_running = false;
              },
              [&continue_running, &no_errors](
                  const TerminateWithError & /*status*/) noexcept {
                continue_running = false;
                no_errors = false;
              },
              [&continue_running, &reissue](
                  const ReissueEvent & /*status*/) noexcept {
                reissue = true;
                continue_running = true;
              },
          },
          execution_status);
      if (continue_running) {
        if (reissue) {
          reissue = false;
          // reuse the same token again
        } else {
          ++transformed_cursor;
        }
      }
    }
    if (continue_running) {
      if (reissue) {
        reissue = false;
        // reuse the same token again
      } else {
        ++cursor;
      }
    }
  }
  machine.Handle(InputEnd{});

  return no_errors;
}
