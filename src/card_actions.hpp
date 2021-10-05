/*
 * Defines the actions cards can take.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef CARD_ACTIONS_HPP
#define CARD_ACTIONS_HPP

#include <vector>

class GameState;
class InputCheck;
class Admirer;
class Deck;
class Card;

void Emissary(Admirer *admirer);
void Defender(GameState &state, Admirer *aggressor, std::vector<Card> &deck);
void Cleric(GameState &state, Admirer *aggressor);
void Lord(GameState &state, Admirer *aggressor, std::vector<Card> &deck);
void Damsel(Admirer *admirer);
void Archduke(GameState &state, Admirer *admirer, std::vector<Card> &deck);
void Adjudicator(std::vector<Card> &deck, Admirer *admirer);
void Emperor(GameState &state, Admirer *aggressor);
void Duchess(Admirer *admirer);
void GrandDuchess(Admirer *admirer, std::vector<Card> &deck);

#endif // !CARD_ACTIONS_HPP
