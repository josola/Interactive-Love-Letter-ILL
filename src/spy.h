/*
 * spy.h
 * determines capabilites of spy card
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef SPY_h
#define SPY_h

#include "card.h"
#include "player.h"

class Spy : public Card
{
public:
    Spy(const string name, const int value);

    void Action(Player &player);

private:
};

#endif // !SPY_h
