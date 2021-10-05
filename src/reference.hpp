/*
 * Defines the reference card.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef REFERENCE_HPP
#define REFERENCE_HPP

#include <string>

#include "card.hpp"

class Reference : public Card {
	
	public:
		Reference();
		void Print();
		
	protected:
		std::string reference[10] = { "9-Grand Duchess (x1): Out of the round if you play/discard.",
									  "8-Duchess (x1): Must play if you have Emperor or Archduke.",
									  "7-Emperor (x1): Trade hands.",
									  "6-Adjudicator (x2): Draw & return 2 cards.",
									  "5-Archduke (x2): Discard a hand & redraw.",
									  "4-Damsel (x2): Immune to other cards until your next turn.",
									  "3-Lord (x2): Compare hands.",
									  "2-Cleric (x2): Look at a hand.",
									  "1-Defender (x6): Guess a hand.",
									  "0-Emissary (x2): Gain favor if no one else plays/discards a Emissary.", };
};

#endif // !REFERENCE_HPP
