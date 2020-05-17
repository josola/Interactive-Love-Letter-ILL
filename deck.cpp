/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <algorithm>
#include "deck.h"

using std::random_shuffle;
using std::srand;
using std::time;

//getters
vector<CardController> DeckInterface::GetDeck() { return deck_; }
CardController DeckInterface::GetCard(int pos)
{
    CardController card = deck_.at(pos);
    RemoveCard(pos);
    return card;
}

//setters
void DeckInterface::InsertCard(CardController card) { deck_.push_back(card); }

//actions
void DeckInterface::Shuffle()
{
    srand(static_cast<unsigned int>(time(NULL)));
    random_shuffle(deck_.begin(), deck_.end());
}
void DeckInterface::RemoveCard(int pos) { deck_.erase(deck_.begin() + pos); }


//builds deck
void DeckController::Builder()
{
    CardController cardController("", 10);
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(0));
    }
    for (int i = 0; i < 6; i++)
    {
        InsertCard(cardController.Builder(1));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(2));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(3));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(4));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(5));
    }
    for (int i = 0; i < 2; i++)
    {
        InsertCard(cardController.Builder(6));
    }
    InsertCard(cardController.Builder(7));
    InsertCard(cardController.Builder(8));
    InsertCard(cardController.Builder(9));
}

//builds up pile (for 2 player games)
void UpController::Builder(DeckController deck)
{
    for (int i = 0; i < 3; i++)
    {
        InsertCard(deck.GetCard(0));
    }
}