//===-- card_actions.h - Card action definitions -------*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines the capabilities of a card action.
///
//===----------------------------------------------------------------------===//

#ifndef CARD_ACTIONS_h
#define CARD_ACTIONS_h

#include <vector>

using std::vector;

class GameState;
class InputCheck;
class Admirer;
class Deck;
class Card;

// actions
void Emissary(Admirer *admirer);
void Defender(GameState &state, Admirer *aggressor, vector<Card> &deck);
void Cleric(GameState &state, Admirer *aggressor);
void Lord(GameState &state, Admirer *aggressor, vector<Card> &deck);
void Damsel(Admirer *admirer);
void Archduke(GameState &state, Admirer *admirer, vector<Card> &deck);
void Adjudicator(vector<Card> &deck, Admirer *admirer);
void Emperor(GameState &state, Admirer *aggressor);
void Duchess(Admirer *admirer);
void GrandDuchess(Admirer *admirer, vector<Card> &deck);

#endif // !CARD_ACTIONS_h
