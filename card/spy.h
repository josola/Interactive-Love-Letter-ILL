/*
 * Determines capabilites of spy card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */


#ifndef SPY_h
#define SPY_h

#include "card.h"
#include "player.h"

class Spy : public Card
{
public:
    Spy(const string name, const int value);

    void Action(PlayerController &player);
};

#endif // !SPY_h
