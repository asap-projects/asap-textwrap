.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

****************************
Advanced indentation control
****************************

.. |date| date::

Last Updated on |date|

You can control the indentation of lines during the wrapping of the text by
setting and indentation prefix for the first line and for the rest of the lines.
This is typically helpful for texts that contain definitions, headers, or if you
want paragraphs to start with first line indented.

Here is an example that displays a list of definitions:

.. code-block:: c++

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
        TextWrapper::Create().Width(column_width).TrimLines();

    std::cout << term_wrapper.Fill(term).value_or("error") << std::endl;

    for (std::vector<std::string>::size_type index = 0;
        index < definitions.size(); index++) {

      constexpr auto prefix_width = 6;
      std::ostringstream first_line_prefix;
      first_line_prefix << std::setw(prefix_width - 2) << std::right << index
                        << "  ";
      std::string other_lines_prefix(prefix_width, ' ');
      TextWrapper definition_wrapper = TextWrapper::Create()
                                          .Width(column_width)
                                          .TrimLines()
                                          .IndentWith()
                                          .Initially(first_line_prefix.str())
                                          .Then(other_lines_prefix);

      std::cout << definition_wrapper.Fill(definitions[index]).value_or("error")
                << "\n\n";
    }
  }

Notice how we indent the definitions according to their index, using the index
text as a prefix for the first line and then indenting the rest of the lines
with an equivalent number of spaces.

The result of this wrapping is a nicely formatted dictionary output for the
definitions of the word 'gorgeous'.

::

  gorgeous [ gawr-juhs ]

  adjective
    0  splendid or sumptuous in appearance, coloring, etc.;
       magnificent: a gorgeous gown; a gorgeous sunset.

    1  Informal. extremely good, enjoyable, or pleasant: I
       had a gorgeous time.
