/*
 * Helper utility for deck.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef DECK_h
#define DECK_h

#include <vector>
#include "card.h"

using std::vector;

class DeckModel
{
protected:
    vector<CardController> deck_;
};

class DeckInterface : public DeckModel
{
public:
    //getters
    vector<CardController> GetDeck();
    CardController GetCard(int pos);

    //setters
    void InsertCard(CardController card);

    //actions
    void Shuffle();
    void RemoveCard(int pos);
};

class DeckController : public DeckInterface
{
public:
    void Builder();
};

class UpController : public DeckInterface
{
public:
    void Builder(DeckController deck);
};

class DownController : public DeckInterface
{
};

#endif