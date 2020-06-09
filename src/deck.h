/*
 * deck.h
 * determines capabilites of the deck
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef DECK_h
#define DECK_h

#include <vector>
#include "card.h"

using std::vector;

class Deck
{
public:
    //getters
    const vector<Card> GetDeck();
    const Card GetCard(int pos);

    //setters
    void InsertCard(const Card card);

    //actions
    void Shuffle();
    void RemoveCard(const int pos);

private:
    vector<Card> deck_;
};

class DeckController : public Deck
{
public:
    void Builder();
};

class UpPile : public Deck
{
public:
    void Builder(DeckController deck);
};

class DownPile : public Deck
{
};

#endif