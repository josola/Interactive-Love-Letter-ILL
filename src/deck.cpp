/*
 * deck.cpp
 * implementation for deck.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include <random>
#include <ctime>
#include <algorithm>
#include "deck.h"
#include "suits.h"

using std::random_shuffle;
using std::srand;
using std::time;

//getters
const vector<Card> Deck::GetDeck() {
    return deck_;
}
const Card Deck::GetCard(int pos) {
    return deck_.at(pos);
}

//setters
void Deck::InsertCard(const Card card) {
    deck_.push_back(card);
}

//actions
void Deck::Shuffle() {
    srand(static_cast<unsigned int>(time(NULL)));
    random_shuffle(deck_.begin(), deck_.end());
}
void Deck::RemoveCard(int pos) {
    deck_.erase(deck_.begin() + pos);
}


//builds deck
void DeckController::Builder() {
    for (int i = 0; i < 2; i++) {
        InsertCard(Spy("SPY[0}", 0));
    }
    for (int i = 0; i < 6; i++) {
        InsertCard(Guard("GUARD[1]", 1));
    }
    for (int i = 0; i < 2; i++) {
        InsertCard(Priest("PRIEST[2]", 2));
    }
    for (int i = 0; i < 2; i++) {
        InsertCard(Baron("BARON[3]", 3));
    }
    for (int i = 0; i < 2; i++) {
        InsertCard(Handmaid("HANDMAID[4]", 4));
    }
    for (int i = 0; i < 2; i++) {
        InsertCard(Prince("PRINCE[5]", 5));
    }
    for (int i = 0; i < 2; i++) {
        InsertCard(Chancellor("CHANCELLOR[6]", 6));
    }
    InsertCard(King("KING[7]", 7));
    InsertCard(Countess("COUNTESS[8]", 8));
    InsertCard(Princess("PRINCESS[9]", 9));
}

//builds up pile (for 2 player games)
void UpPile::Builder(DeckController deck) {
    for (int i = 0; i < 3; i++) {
        InsertCard(deck.GetCard(0));
        RemoveCard(0);
    }
}