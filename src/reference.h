//===-- reference.h - Reference class definition -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the Reference card class. This card is the reference
/// for players to view during gameplay.
///
//===----------------------------------------------------------------------===//

#ifndef REFERENCE_H
#define REFERENCE_H

#include "card.h"
#include <string>

using std::string;

class Reference : public Card
{
public:
  Reference();
  void Print();

protected:
  string reference[10] = {
      "9-Grand Duchess (x1): Out of the round if you play/discard.",
      "8-Duchess (x1): Must play if you have Emperor or Archduke.",
      "7-Emperor (x1): Trade hands.",
      "6-Adjudicator (x2): Draw & return 2 cards.",
      "5-Archduke (x2): Discard a hand & redraw.",
      "4-Damsel (x2): Immune to other cards until your next turn.",
      "3-Lord (x2): Compare hands.",
      "2-Cleric (x2): Look at a hand.",
      "1-Defender (x6): Guess a hand.",
      "0-Emissary (x2): Gain favor if no one else plays/discards a Emissary.",
  };
};

#endif
