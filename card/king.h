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
	~King();

private:

};

King::King(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

King::~King()
{
}

#endif // !KING_h
