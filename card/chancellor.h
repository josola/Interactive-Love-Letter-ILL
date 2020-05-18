/*
 * Determines capabilites of chancellor card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CHANCELLOR_h
#define CHANCELLOR_h

#include "card.h"

class Chancellor : public Card
{
public:
	Chancellor(const string name, const int value);
	~Chancellor();

private:

};

Chancellor::Chancellor(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

Chancellor::~Chancellor()
{
}

#endif // !CHANCELLOR_h
