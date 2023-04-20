//===----------------------------------------------------------------------===//
// Distributed under the 3-Clause BSD License. See accompanying file LICENSE or
// copy at https://opensource.org/licenses/BSD-3-Clause).
// SPDX-License-Identifier: BSD-3-Clause
//===----------------------------------------------------------------------===//

#include <textwrap/textwrap.h>

#include <iostream>

using asap::wrap::TextWrapper;

auto main(int /*argc*/, const char ** /*argv*/) -> int {
  const auto *passage =
      " There was a certain island in the sea, the only inhabitants of which "
      "were an old man, whose name was Prospero, and his daughter Miranda, a "
      "very beautiful young lady. She came to this island so young, that she "
      "had no memory of having seen any other human face than her "
      "father's.\n\nThey lived in a cave or cell, made out of a rock; it was "
      "divided into several apartments, one of which Prospero called his "
      "study; there he kept his books, which chiefly treated of magic, a study "
      "at that time much affected by all learned men: and the knowledge of "
      "this art he found very useful to him; for being thrown by a strange "
      "chance upon this island, which had been enchanted by a witch called "
      "Sycorax, who died there a short time before his arrival, Prospero, by "
      "virtue of his art, released many good spirits that Sycorax had "
      "imprisoned in the bodies of large trees, because they had refused to "
      "execute her wicked commands. These gentle spirits were ever after "
      "obedient to the will of Prospero. Of these Ariel was the chief.\n\nThe "
      "lively little sprite Ariel had nothing mischievous in his nature, "
      "except that he took rather too much pleasure in tormenting an ugly "
      "monster called Caliban, for he owed him a grudge because he was the son "
      "of his old enemy Sycorax. This Caliban, Prospero found in the woods, a "
      "strange misshapen thing, far less human in form than an ape: he took "
      "him home to his cell, and taught him to speak; and Prospero would have "
      "been very kind to him, but the bad nature which Caliban inherited from "
      "his mother Sycorax, would not let him learn anything good or useful: "
      "therefore he was employed like a slave, to fetch wood, and do the most "
      "laborious offices; and Ariel had the charge of compelling him to these "
      "services.";

  constexpr size_t column_width = 70;
  const TextWrapper wrapper =
      asap::wrap::MakeWrapper().Width(column_width).TrimLines();

  std::cout << wrapper.Fill(passage).value_or("error") << std::endl;

  // There was a certain island in the sea, the only inhabitants of which
  // were an old man, whose name was Prospero, and his daughter Miranda, a
  // very beautiful young lady. She came to this island so young, that she
  // had no memory of having seen any other human face than her father's.

  // They lived in a cave or cell, made out of a rock; it was divided into
  // several apartments, one of which Prospero called his study; there he
  // kept his books, which chiefly treated of magic, a study at that time
  // much affected by all learned men: and the knowledge of this art he
  // found very useful to him; for being thrown by a strange chance upon
  // this island, which had been enchanted by a witch called Sycorax, who
  // died there a short time before his arrival, Prospero, by virtue of
  // his art, released many good spirits that Sycorax had imprisoned in the
  // bodies of large trees, because they had refused to execute her wicked
  // commands. These gentle spirits were ever after obedient to the will of
  // Prospero. Of these Ariel was the chief.

  // The lively little sprite Ariel had nothing mischievous in his nature,
  // except that he took rather too much pleasure in tormenting an ugly
  // monster called Caliban, for he owed him a grudge because he was the
  // son of his old enemy Sycorax. This Caliban, Prospero found in the
  // woods, a strange misshapen thing, far less human in form than an ape:
  // he took him home to his cell, and taught him to speak; and Prospero
  // would have been very kind to him, but the bad nature which Caliban
  // inherited from his mother Sycorax, would not let him learn anything
  // good or useful: therefore he was employed like a slave, to fetch
  // wood, and do the most laborious offices; and Ariel had the charge of
  // compelling him to these services.
}
