.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

**********
Public API
**********

.. |date| date::

Last Updated on |date|

The header `<textwrap/textwrap.h>`` declares the classes
:class:`asap::wrap::TextWrapper` and :class:`asap::wrap::TextWrapperBuilder`
which form the core of the text wrapper module public API.

TextWrapper
===========

.. doxygenclass:: asap::wrap::TextWrapper
   :project: textwrap
   :members:

TextWrapperBuilder
==================

.. doxygenclass:: asap::wrap::TextWrapperBuilder
   :project: textwrap
   :members:
