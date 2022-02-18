.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

State Machine Exceptions
========================

While state event handlers use primarily the asap::fsm::ReportError action to
transmit errors to the state machine, other places in the implementation such as
the OnEnter() or OnLeave() methods in states do not have access to actions, and
therefore report errors as exceptions.

.. doxygenclass:: asap::fsm::StateMachineError
   :members:
