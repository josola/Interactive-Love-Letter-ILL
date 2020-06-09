/*
 * prince.h
 * determines capabilites of prince card
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef PRINCE_h
#define PRINCE_h

#include "card.h"

class Prince : public Card
{
public:
    Prince(const string name, const int value);

    void Action();

private:
};

#endif // !PRINCE_h
