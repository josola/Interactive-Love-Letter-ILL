/*
 * Determines capabilites of spy card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */


#ifndef SPY_h
#define SPY_h

#include "card.h"

class Spy : public CardInterface
{
public:
    Spy(string name, int value);
};

#endif // !SPY_h
