#######################################
ASAP State Machine module documentation
#######################################

.. toctree::
   :maxdepth: 2
   :hidden:

   Tutorial <tutorial>
   API <api>
   License <license>
   Version <version>

Welcome! This is the documentation for the *fsm* module, part of the *asap*
project. This is a feature module providing a framework to quickly build type
safe state machines using C++17 and templates.

A state machine has a set of possible states and a set of rules that govern
transitions between the current state and some other state upon receiving an
event.

A state can be an arbitrary object, which type is used to distinguish it from
other states. Therefore, there is no need to maintain a list of known states
(in an enumeration for example). We also don't want to enforce any
relationship between those types to keep them completely independent. The
state machine is a variadic template that gets to know its states through the
parameter pack and stores them in a tuple.

Transitions from the current state to other states are triggered by events.
This requires that all the state types have a `Handle` method that accepts an
event of the type of event being handled. To avoid creating unnecessary
dependencies between the state types and the state machine type, a state's
`Handle` method will return an object of a specific type (an action) that
will describe what action should the machine take.

Events are produced outside the state machine and fed into it by an external
event loop which calls the state machine's `Handle` method. The latter
dispatches the event to the current state, which returns a specific action
that gets executed to eventually transition to a new state.

Examples and detailed documentation of the API can be found at the
[Project Documentation](https://asap-projects.github.io/asap-fsm/) pages.

Parts of the documentation
==========================

:doc:`API reference <api>`
------------------------------
  *check this out to see the documentation of classes, macros, etc. offered by
  this module*
