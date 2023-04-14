.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

###############################
ASAP text wrapper documentation
###############################

.. |date| date::

Last Updated on |date|

.. toctree::
   :maxdepth: 2
   :hidden:

   Usage <usage>
   API <api>
   License <license>
   Version <version>

Welcome! This is the documentation for the *textwrap* module, part of the *asap*
project.

This module simplifies the task of formatting text in fixed width columns and
indenting it properly. Often, applications that needs to pretty print text or
display data in tabular format end up doing the alignment, indentation and
wrapping of each line manually by hardcoding spaces, tabs and line breaks or by
just assuming that display width is unlimited (which is not true).

With this library, wrapping long lines of text while maintaining indentation
requirements and proper line breaks management is straightforward.

Here is a simple example: the following text unwrapped would be presented as a
single very long line:

  There were doors all round the hall, but they were all locked; and when Alice
  had been all the way down one side and up the other, trying every door, she
  walked sadly down the middle, wondering how she was ever to get out again.

But when wrapped at 50 characters per line, it will display nicely within the
limited available width:

  .. image:: /_static/simple-wrapped-text.png
    :width: 500
    :alt: Text wrapped at 50 characters maximum width.

The capabilities of the library go much further with the following additional
features:

- **Indentation** using any prefix string, which can be different for the first
  line of each paragraph.
- **Tab expansion**, where each `tab` character is expanded to a replacement
  string (can be spaces or anything else).
- **Space replacement**, where each spacing character (including `<SPACE>`,
  `\t`, `\f`, `\r`) is replaced by a single space (' ').
- **Space collapsing**, where multiple consecutive spacing characters are
  replaced with a single space (' ').
- **Line trimming**, where spaces at the start or end of a line are eliminated.
- **Breaking on hyphens**, where compound words will be broken into separate
  chunks right after hyphens, as it is customary in English.

Parts of the documentation
==========================

:doc:`Detailed usage <usage>`
-----------------------------
   *start here to understand how to build wrappers and see examples of different
   wrapper configurations in action.*

:doc:`API reference <api>`
--------------------------
   *check this out to see the documentation of classes, macros, etc. offered by
   this module*
