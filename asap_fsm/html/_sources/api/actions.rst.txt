.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

State Machine Actions
=====================

Actions are returned from state event handlers and are the normal way of
communicating back to the state machine what to do next. The only requirement on
an Action type is to have an Execute() method, that gets the state machine
instance, the current state and the event being processed.

Additional type management utility methods are added to action classes as needed
to simplify the unit testing of the states and actions. They are in no way used
in the basic functioning of a state machine which totally relies on static
compile-time types and rules.

.. doxygenstruct:: asap::fsm::TransitionTo
   :members:

.. doxygenstruct:: asap::fsm::DoNothing
   :members:

.. doxygenstruct:: asap::fsm::ReportError
   :members:

.. doxygenstruct:: asap::fsm::OneOf
   :members:

.. doxygenstruct:: asap::fsm::Maybe
   :members:

.. doxygenstruct:: asap::fsm::is_one_of

.. doxygenfunction:: asap::fsm::supports_alternative
