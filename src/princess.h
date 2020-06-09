/*
 * princess.h
 * determines capabilites of princess card
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef PRINCESS_h
#define PRINCESS_h

#include "card.h"

class Princess : public Card
{
public:
    Princess(const string name, const int value);

    void Action();

private:
};

#endif // !PRINCESS_h
