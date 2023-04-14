//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

/*!
 * \file
 *
 * \brief Implementation details of the Column class.
 */

#include "textwrap/textwrap.h"

#include <cstddef>
#include <iostream>
#include <limits>
#include <numeric>
#include <optional>
#include <utility>

#include "tokenizer.h"

auto asap::wrap::operator<<(std::ostream &out,
    const asap::wrap::TextWrapper &wrapper) -> std::ostream & {
  out << "{w:" << wrapper.width_ << ",t:'" << wrapper.tab_
      << "',rw:" << wrapper.replace_ws_ << ",tl:" << wrapper.trim_lines_
      << ",boh:" << wrapper.break_on_hyphens_ << "}";
  return out;
}

namespace {

auto WrapChunks(const std::vector<asap::wrap::detail::Token> &chunks,
    size_t width, const std::string &indent, const std::string &initial_indent,
    bool trim_lines) -> std::vector<std::string> {

  // https://www.geeksforgeeks.org/word-wrap-problem-space-optimized-solution/

  const auto num_chunks = chunks.size();
  const auto first_line_width = width - initial_indent.size();
  const auto other_line_width = width - indent.size();

  size_t cur_chunk{0};
  size_t cur_chunk_in_line{0};

  // Table in which costs[index] represents cost of line starting with word
  // chunks[index].
  std::vector<size_t> costs(num_chunks);

  // Table in which optimized[index] stores index of the last word in line
  // starting with word chunks[index].
  std::vector<size_t> optimized(num_chunks);

  // If only one word is present then only one line is required. Cost of last
  // line is zero. Hence cost of this line is zero. Ending point is also n-1 as
  // single word is present.
  costs[num_chunks - 1] = 0;
  optimized[num_chunks - 1] = num_chunks - 1;

  if (num_chunks > 1) {

    // Variable to store possible minimum cost of line.
    size_t cost{0};

    // Make each word first word of line by iterating over each index in arr.
    cur_chunk = num_chunks - 1;
    do {
      cur_chunk--;

      // Variable to store number of characters in given line.
      size_t currlen{0};

      costs[cur_chunk] = std::numeric_limits<size_t>::max();
      const auto adjusted_width =
          (cur_chunk == 0 ? first_line_width : other_line_width);

      cur_chunk_in_line = cur_chunk;
      auto first_chunk_in_line = cur_chunk_in_line;

      // The new line token can either have a size that will break the maximum
      // width or a size of zero depending on whether it is the first chunk,
      // the first in the line or just part of a next line.
      if (chunks[cur_chunk_in_line].first ==
          asap::wrap::detail::TokenType::NewLine) {
        if (cur_chunk_in_line != first_chunk_in_line) {
          currlen = adjusted_width + 1;
        } else {
          first_chunk_in_line++;
          cur_chunk_in_line++;
        }
      }

      if (trim_lines) {
        // Skip all white space chunks at start as they will be trimmed later
        while (cur_chunk_in_line < num_chunks &&
               (chunks[cur_chunk_in_line].first ==
                   asap::wrap::detail::TokenType::WhiteSpace)) {
          cur_chunk_in_line++;
          first_chunk_in_line++;
        }
      }
      // Keep on adding words in current line by iterating from starting word
      // up to last word in arr.
      while (cur_chunk_in_line < num_chunks) {

        // Update number of characters in current line.
        // The new line token can either have a size that will break the maximum
        // width or a size of zero depending on whether it is the first chunk,
        // the first in the line or just part of a next line.
        if (chunks[cur_chunk_in_line].first ==
            asap::wrap::detail::TokenType::NewLine) {
          if (cur_chunk_in_line != first_chunk_in_line) {
            currlen = adjusted_width + 1;
          }
        } else {
          currlen += (chunks[cur_chunk_in_line].second.size());
        }

        // If limit of characters is violated then no more words can be added to
        // current line, unless what we are adding is white space and we've been
        // configured to trim white space.
        if (currlen > adjusted_width) {
          if (chunks[cur_chunk_in_line].first ==
                  asap::wrap::detail::TokenType::WhiteSpace &&
              trim_lines) {
            // Will be trimmed later so don't count it
            currlen -= (chunks[cur_chunk_in_line].second.size());
          }
          // Abort adding the current chunk to the current line, unless it is
          // the only chunk in the line. In that case, we accept it even if it's
          // going to make the line longer than the maximum adjusted width.
          else if (cur_chunk_in_line > first_chunk_in_line) {
            break;
          }
        }

        // If current chunk being added to the line is the last chunk then
        // current line is the last line. Cost of last line is 0. Else cost is
        // square of extra spaces plus cost of putting line breaks in rest of
        // words from j+1 to n-1.
        if (cur_chunk_in_line == num_chunks - 1) {
          cost = 0;
        } else {
          cost = (adjusted_width - currlen) * (adjusted_width - currlen) +
                 costs[cur_chunk_in_line + 1];
        }

        // Check if this arrangement gives minimum cost for line starting with
        // word arr[index_i].
        if (cost < costs[cur_chunk]) {
          costs[cur_chunk] = cost;
          optimized[cur_chunk] = cur_chunk_in_line;
        }

        // if (currlen > adjusted_width) {
        //   break;
        // }
        cur_chunk_in_line++;
      }
    } while (cur_chunk > 0);
  }

  // Print starting index and ending index of words present in each line.
  std::vector<std::string> result;
  cur_chunk = 0;
  auto first_line{true};
  while (cur_chunk < num_chunks) {
    // std::cout << cur_chunk + 1 << " " << optimized[cur_chunk] + 1 << " : ";
    std::string line = cur_chunk == 0 ? initial_indent : indent;
    size_t start = cur_chunk;
    size_t end = optimized[cur_chunk] + 1;
    // Always trim new lines (eventually creating an empty line if needed), and
    // if TrimLines is true, then also trim whitespaces
    while (start < end) {
      if (chunks[start].first == asap::wrap::detail::TokenType::NewLine) {
        if (first_line) {
          // Add an empty line and continue
          result.emplace_back(line);
          line = indent;
        }
        start++;
        if (start == end) {
          break;
        }
      } else if (trim_lines && (chunks[start].first ==
                                   asap::wrap::detail::TokenType::WhiteSpace)) {
        start++;
        if (start == end) {
          // Add an empty line and continue
          result.emplace_back(line);
          line = indent;
        }
      } else {
        break;
      }
    }
    while ((end - 1) > start) {
      if ((trim_lines && (chunks[end - 1].first ==
                             asap::wrap::detail::TokenType::WhiteSpace))) {
        end--;
        if (start == end) {
          // Add an empty line and continue
          result.emplace_back(line);
          line = indent;
        }
      } else {
        break;
      }
    }
    if (end > start) {
      for (cur_chunk_in_line = start; cur_chunk_in_line < end;
           cur_chunk_in_line++) {
        // std::cout << chunks[cur_chunk_in_line].second;
        line.append(chunks[cur_chunk_in_line].second);
      }
      result.push_back(std::move(line));
      // std::cout << std::endl;
    }
    cur_chunk = optimized[cur_chunk] + 1;
    first_line = false;
  }

  return result;
}

void MoveAppend(std::vector<std::string> src, std::vector<std::string> &dst) {
  if (dst.empty()) {
    dst = std::move(src);
  } else {
    dst.reserve(dst.size() + src.size());
    std::move(std::begin(src), std::end(src), std::back_inserter(dst));
    src.clear();
  }
}
} // namespace

[[nodiscard]] auto asap::wrap::TextWrapper::Wrap(const std::string &str) const
    -> std::optional<std::vector<std::string>> {
  const auto tokenizer =
      detail::Tokenizer(tab_, replace_ws_, collapse_ws_, break_on_hyphens_);

  std::vector<std::string> result;
  std::vector<detail::Token> chunks;
  const detail::TokenConsumer consume_token = [&chunks, this, &result](
                                                  detail::TokenType token_type,
                                                  std::string token) -> void {
    if ((token_type == detail::TokenType::ParagraphMark ||
            token_type == detail::TokenType::EndOfInput) &&
        !chunks.empty()) {
      if (!result.empty()) {
        result.emplace_back("");
      }
      MoveAppend(
          WrapChunks(chunks, width_, indent_, initial_indent_, trim_lines_),
          result);
      chunks.clear();
    } else {
      chunks.emplace_back(token_type, std::move(token));
    }
  };

  if (tokenizer.Tokenize(str, consume_token)) {
    return std::make_optional(result);
  }

  return {};
}
[[nodiscard]] auto asap::wrap::TextWrapper::Fill(const std::string &str) const
    -> std::optional<std::string> {

  const auto wrap_opt = Wrap(str);
  if (!wrap_opt) {
    return {};
  }
  const auto &wrap = wrap_opt.value();
  std::string result;
  auto size = std::accumulate(wrap.cbegin(), wrap.cend(),
      static_cast<size_t>(0), [](size_t acc, const std::string &line) {
        return acc + line.length() + 1;
      });
  if (size > 0) {
    size -= 1; // remove the end of line from the last line
  }
  result.resize(size);
  [[maybe_unused]] auto acc = std::accumulate(wrap.cbegin(), wrap.cend(),
      result.begin(), [&result](const auto &dest, const std::string &line) {
        auto next_write = std::copy(line.cbegin(), line.cend(), dest);
        // Do not add a '\n' at the end of the string
        if (next_write != result.end()) {
          *next_write = '\n';
          ++next_write;
        }
        return next_write;
      });
  return std::make_optional(result);
}

auto asap::wrap::TextWrapper::Create() -> asap::wrap::TextWrapperBuilder {
  return {};
}

auto asap::wrap::TextWrapperBuilder::Width(size_t width)
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.width_ = width;
  return *this;
}

auto asap::wrap::TextWrapperBuilder::IndentWith()
    -> asap::wrap::TextWrapperBuilder & {
  return *this;
}

auto asap::wrap::TextWrapperBuilder::Initially(std::string initial_indent)
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.initial_indent_ = std::move(initial_indent);
  return *this;
}

auto asap::wrap::TextWrapperBuilder::Then(std::string indent)
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.indent_ = std::move(indent);
  return *this;
}

auto asap::wrap::TextWrapperBuilder::ExpandTabs(std::string tab)
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.tab_ = std::move(tab);
  return *this;
}

auto asap::wrap::TextWrapperBuilder::ReplaceWhiteSpace()
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.replace_ws_ = true;
  return *this;
}

auto asap::wrap::TextWrapperBuilder::CollapseWhiteSpace()
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.collapse_ws_ = true;
  return *this;
}

auto asap::wrap::TextWrapperBuilder::TrimLines()
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.trim_lines_ = true;
  return *this;
}

auto asap::wrap::TextWrapperBuilder::BreakOnHyphens()
    -> asap::wrap::TextWrapperBuilder & {
  wrapper.break_on_hyphens_ = true;
  return *this;
}
