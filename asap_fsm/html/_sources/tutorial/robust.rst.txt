.. Structure conventions
    # with overline, for parts
    * with overline, for chapters
    = for sections
    - for subsections
    ^ for sub-subsections
    " for paragraphs

****************************
Tutorial: A more robust door
****************************

So far, we have created the door state machine with two states (Open and
Closed), but we don't like the fact that the current implementation does not
check if the door is already open or already closed when someone attempts to
open/close it.

We want the implementation to report an error when such cases happen. For that,
we will use custom event handlers.

We will also use this opportunity to simplify the diagnostics of the state
machine by having the states themselves report when enter/leave them. For that
we will use the `OnEnter()` method. OnEnter/OnLeave are optional, but when they
are present, they get called during state transitions. For this example, we will
omit the `OnLeave` method as we just want to report the new state.

.. literalinclude:: /../examples/tutorial/door_2.cpp
  :lines: 7-
  :linenos:

Notice how we define a template method for OnEnter that gets called on any type
of event. We could also write OnEnter handlers for a specific type of event.
Such handlers will only get called when the event type matches the handler's
signature (templates SFINAE).

If we run that example, this is what we get:

.. code-block:: text

  -- Starting
  -- sending close event
  Error: the door is already closed!
  -- sending open event
    > door is open
  -- sending open event
  Error: the door is already open!
  -- sending close event
    > door is closed

Now, we want to make our door more secure by adding a lock pad and a code that
will be required to unlock it once it is locked.

Head over to the :doc:`next step <secure>` to see how we can do that.
