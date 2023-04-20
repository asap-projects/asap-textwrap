.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

*********************
Typical wrapper usage
*********************

.. |date| date::

Last Updated on |date|

The most typical case is reformatting plain text to fit a specific column width
for style or to show in a limited width display such as a terminal. The text can
contain multiple paragraphs (or blocks) separated by a double line break (i.e.
an empty line).

The result of text wrapping can be obtained either as a list of lines or as a
string created by concatenating these lines (appending end of lines as
appropriate).

In the following example we take a text from the book `Tales from Shakespeare by
Charles and Mary Lamb
<https://www.gutenberg.org/cache/epub/573/pg573-images.html#tempest>`_ and we
reformat it to fit into a maximum width of 70 characters per line.

Notice the use of `TrimLines()` which will eliminate leading and trailing spaces
after the wrapping is done. Also note how paragraphs are demarcated by a double
line break (`\n\n`).

.. code-block:: c++

  #include <textwrap/textwrap.h>

  #include <iostream>

  using asap::wrap::TextWrapper;

  auto main(int /*argc*/, const char ** /*argv*/) -> int {
    const auto *passage =
        "There was a certain island in the sea, the only inhabitants of which "
        "were an old man, whose name was Prospero, and his daughter Miranda, a "
        "very beautiful young lady. She came to this island so young, that she "
        "had no memory of having seen any other human face than her "
        "father's.\n\nThey lived in a cave or cell, made out of a rock; it was "
        "divided into several apartments, one of which Prospero called his "
        "study; there he kept his books, which chiefly treated of magic, a study "
        "at that time much affected by all learned men: and the knowledge of "
        "this art he found very useful to him; for being thrown by a strange "
        "chance upon this island, which had been enchanted by a witch called "
        "Sycorax, who died there a short time before his arrival, Prospero, by "
        "virtue of his art, released many good spirits that Sycorax had "
        "imprisoned in the bodies of large trees, because they had refused to "
        "execute her wicked commands. These gentle spirits were ever after "
        "obedient to the will of Prospero. Of these Ariel was the chief.\n\nThe "
        "lively little sprite Ariel had nothing mischievous in his nature, "
        "except that he took rather too much pleasure in tormenting an ugly "
        "monster called Caliban, for he owed him a grudge because he was the son "
        "of his old enemy Sycorax. This Caliban, Prospero found in the woods, a "
        "strange misshapen thing, far less human in form than an ape: he took "
        "him home to his cell, and taught him to speak; and Prospero would have "
        "been very kind to him, but the bad nature which Caliban inherited from "
        "his mother Sycorax, would not let him learn anything good or useful: "
        "therefore he was employed like a slave, to fetch wood, and do the most "
        "laborious offices; and Ariel had the charge of compelling him to these "
        "services.";

    constexpr size_t column_width = 70;
    const TextWrapper wrapper =
        asap::wrap::MakeWrapper().Width(column_width).TrimLines();

    std::cout << wrapper.Fill(passage).value_or("error") << std::endl;
  }

The result of this wrapping is a nicely formatted text where every line has a
maximum length of `70`.

::

  There was a certain island in the sea, the only inhabitants of which
  were an old man, whose name was Prospero, and his daughter Miranda, a
  very beautiful young lady. She came to this island so young, that she
  had no memory of having seen any other human face than her father's.

  They lived in a cave or cell, made out of a rock; it was divided into
  several apartments, one of which Prospero called his study; there he
  kept his books, which chiefly treated of magic, a study at that time
  much affected by all learned men: and the knowledge of this art he
  found very useful to him; for being thrown by a strange chance upon
  this island, which had been enchanted by a witch called Sycorax, who
  died there a short time before his arrival, Prospero, by virtue of
  his art, released many good spirits that Sycorax had imprisoned in the
  bodies of large trees, because they had refused to execute her wicked
  commands. These gentle spirits were ever after obedient to the will of
  Prospero. Of these Ariel was the chief.

  The lively little sprite Ariel had nothing mischievous in his nature,
  except that he took rather too much pleasure in tormenting an ugly
  monster called Caliban, for he owed him a grudge because he was the
  son of his old enemy Sycorax. This Caliban, Prospero found in the
  woods, a strange misshapen thing, far less human in form than an ape:
  he took him home to his cell, and taught him to speak; and Prospero
  would have been very kind to him, but the bad nature which Caliban
  inherited from his mother Sycorax, would not let him learn anything
  good or useful: therefore he was employed like a slave, to fetch
  wood, and do the most laborious offices; and Ariel had the charge of
  compelling him to these services.
