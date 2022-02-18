.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

State Machine State Types
=========================

A number of helper base classes for implementing states are provided. These are
intended for simplifying typical obvious event processing cases and for allowing
to easily implement the unique interface of event handlers always returning an
Action.

.. doxygenstruct:: asap::fsm::On
   :members:

.. doxygenstruct:: asap::fsm::ByDefault
   :members:

.. doxygenstruct:: asap::fsm::Will
   :members:
