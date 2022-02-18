.. Structure conventions
    # with overline, for parts
    * with overline, for chapters
    = for sections
    - for subsections
    ^ for sub-subsections
    " for paragraphs

**********************
Tutorial: A basic door
**********************

In this tutorial we will use the `asap::fsm` toolkit to implement a state
machine simulating a door. We'll start with two states (Closed and Open) and
two events (Open and Close). The state machine can be represented by the
following diagram:

.. image:: /_static/door_two_states.png
  :width: 400
  :alt: Door states
  :align: center

.. literalinclude:: /../examples/tutorial/door_1.cpp
  :lines: 7-
  :linenos:
  :emphasize-lines: 18-25

The implementation is pretty straightforward for such a simple state machine:

1. Define the events. Event types don't need to be complex types. In this case,
   they are simple type tags. In other more complicated cases, events can carry
   data as well.

2. Define the states.

   We can completely implement states with simple transition logic, such as in
   this example, declaratively. In lines 18-25, we use the state helpers `Will`,
   `On` and `ByDefault` to implement the logic of the ClosedState.

3. Declare the State Machine. It's always a good practice to use an alias for
   the State Machine type so that you don't have to repeat the often very long
   type declaration.

From there on, using the state machine is a matter of injecting events into it
via calls to its `Handle()` method.

If we run that example, this is what we get:

.. code-block:: text

  -- Starting
    > door is closed
  -- sending close event
    > door is closed
  -- sending open event
    > door is open
  -- sending close event
    > door is closed


Notice how this implementation of the state machine is very basic to the point
where we can close a closed door or open and open one with no error. We'd like
to make it smarter so it can detect such cases and report the error to the user.

Head over to the :doc:`next step <robust>` to see how we can do that.
