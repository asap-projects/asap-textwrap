.. Structure conventions
     # with overline, for parts
     * with overline, for chapters
     = for sections
     - for subsections
     ^ for sub-subsections
     " for paragraphs

********
Tutorial
********

.. toctree::
   :maxdepth: 2
   :hidden:

   Basic door <tutorial/basic>
   Robust door <tutorial/robust>
   Secure door <tutorial/secure>

In this tutorial we will use the `asap::fsm` toolkit to implement a state
machine simulating a door.

We'll start with a basic door that has no intelligence of any kind and see how
it can be implemented in a couple of lines, and in a completely declarative
fashion.

Next, we'll make the door smarter by making it enforce some rules in each state.

Finally, we'll add some advanced logic to make the door lockable with a secret
code and demonstrate how we can implement state machine states that exchange
data on transitions.

:doc:`Let's get started! <tutorial/basic>`
