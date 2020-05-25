/*
 * Determines capabilites of king card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef KING_h
#define KING_h

#include "card.h"

class King : public Card
{
public:
	King(const string name, const int value);

    void Action();

private:

};

#endif // !KING_h
