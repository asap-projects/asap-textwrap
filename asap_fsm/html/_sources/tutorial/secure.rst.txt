.. Structure conventions
    # with overline, for parts
    * with overline, for chapters
    = for sections
    - for subsections
    ^ for sub-subsections
    " for paragraphs

***********************
Tutorial: A secure door
***********************

In this last step of the tutorial, we'll make our door super smart. We're going
to add a lock code that can be set when locking the door and that will be
required to unlock it later.

We'll assume that the lock code is entered suing some kind of UI interacting
with the user, and which provides it to us in the form of an integer.

The new state machine can be represented by the following diagram:

.. image:: /_static/door_three_states.png
  :width: 300
  :alt: Door states
  :align: center

Besides an additional state, we’ll introduce two new events `Lock` and `Unlock`.
Now, once the door is locked, the only way to open it, is to unlock it first.

.. literalinclude:: /../examples/tutorial/door_3.cpp
  :lines: 7-
  :linenos:

If we run that example, this is what we get:

.. code-block:: text

  -- Starting
  -- sending open event
    > door is open
  -- sending close event
    > door is closed
  -- sending lock event (1234)
    > door is locked with new code(1234)
  -- sending unlock event (2)
  Error: wrong key (2) used to unlock door!
  -- sending unlock event (1234)
    > door is closed - unlocked

The new implementation demonstrates many advanced features offered by the
`asap::fsm` library:

- using templates SFINAE to define custom handlers for specific events,
- passing data in events,
- storing data in states

Additionally, the API allows for passing data during transitions from one state
to another. Check the documentation of `TransitionTo` for additional details on
that technique.

Several sophisticated examples of using the asap::fsm library in real world
projects can be found at:

- `asap-textwrap <https://github.com/asap-projects/asap-textwrap>`_
- `asap-clap <https://github.com/asap-projects/asap-clap>`_
