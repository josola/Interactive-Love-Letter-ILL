/*
 * Determines capabilites of prince card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PRINCE_h
#define PRINCE_h

#include "card.h"

class Prince : public Card
{
public:
	Prince(const string name, const int value);
	~Prince();

private:

};

Prince::Prince(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

Prince::~Prince()
{
}

#endif // !PRINCE_h
