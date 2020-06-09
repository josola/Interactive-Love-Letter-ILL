/*
 * player.h
 * determines player capabilities
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef PLAYER_h
#define PLAYER_h

#include <string>
#include <vector>
#include "card.h"
#include "deck.h"

using std::string;
using std::vector;

class Player
{
public:
    Player(const string name, const int value);

    //getters
    const string Name();
    const int Value();
    const bool Winner();
    const bool Current();
    const bool Spy();
    const int Guess();
    const vector<Card> Hand();
    const bool Playing();
    const int Tokens();

    //setters
    void SetName(const string name);
    void SetValue(const int value);
    void SetCurrent(const bool value);
    void SetWinner(const bool value);
    void SetGuess(const int value);
    void SetPlaying(const bool value);
    void SetHandmaid(const bool value);
    void SetSpy(const bool value);

    //actions
    void InsertIntoHand(const Card& card);
    void RemoveCardFromHand(const int value);
    void ClearHand();
    Card DrawCard(Deck& deck);

private:
    string name_ = " ";
    int value_ = 0;
    bool current_ = false;
    bool winner_ = false;
    int guess_ = 0;
    bool spy_ = false;
    vector<Card> hand_{};
    bool playing_ = true;
    int token_count_ = 0;
    bool handmaid_ = false;
};

#endif // !PLAYER_h