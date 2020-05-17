/*
 * Determines player information and utility.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "player.h"

//getters
const string PlayerInterface::Name() { return name; }
const int PlayerInterface::Value() { return value; }
const int PlayerInterface::Guess() { return guess; }
const bool PlayerInterface::Current() { return current; }
const bool PlayerInterface::Spy() { return spy; }
const bool PlayerInterface::Winner() { return winner; }
vector<CardController> const PlayerInterface::Hand() { return hand; }
constexpr bool const PlayerInterface::Playing() { return playing; }
const int PlayerInterface::Tokens() { return token_count; }

//setters
void PlayerInterface::SetName(string input) { name = input; }
void PlayerInterface::SetValue(int input) { value = input; }
void PlayerInterface::IsCurrent() { current = true; }
void PlayerInterface::NotCurrent() { current = false; }
void PlayerInterface::IsWinner() { winner = true;}
void PlayerInterface::NotWinner() { winner = false; }
void PlayerInterface::SetGuess(int output) { guess = output; }
void PlayerInterface::IsPlaying() { playing = true; }
void PlayerInterface::NotPlaying() { playing = false; }
void PlayerInterface::HasHandmaid() { handmaid = true; }
void PlayerInterface::NoHandmaid() { handmaid = false; }
void PlayerInterface::SetSpy(bool output) { spy = output; }

//actions
CardController PlayerController::DrawCard(DeckController &deck)
{
    CardController top_card = deck.GetCard(0);
    return top_card;
}
void PlayerController::InsertCardIntoHand(CardController card) { hand.push_back(card); }
