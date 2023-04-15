.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

**************************
Cleaning-up spaces in text
**************************

.. |date| date::

Last Updated on |date|

Sometimes the text contains tabs and spacing is not consistent with places where
multiple spacing characters are used while we only need a single space. In that
case, we can use the tab substitution and space collapsing features to cleanup
the text formatting while wrapping it.

Here is an example:

.. code-block:: c++

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
    const TextWrapper wrapper = TextWrapper::Create()
                                    .Width(column_width)
                                    .ExpandTabs("")
                                    .CollapseWhiteSpace()
                                    .IndentWith()
                                    .Initially("")
                                    .Then(" > ");

    std::cout << wrapper.Fill(passage).value_or("error") << std::endl;
  }

Without the processing of spaces and tabs, the text looks like this::

  Miranda said:
          'It seems to me like the recollection of a dream.   But had I not once four or five women who attended upon me?'

  Prospero answered:
          'You had, and more. How is it that this still lives in your mind?  Do you remember how you came here?'

But once we eliminate tabs by expanding them to an empty string, we collapse
multiple spaces into a single space and wrap and indent the quotes with a
special prefix, the text looks completely different and in the format we want.

The result of this wrapping is a nicely formatted dictionary output for the
definitions of the word 'gorgeous'.

::

  Miranda said:
   > 'It seems to me like the recollection of a dream. But had I not
   > once four or five women who attended upon me?'

  Prospero answered:
   > 'You had, and more. How is it that this still lives in your mind?
   > Do you remember how you came here?'
