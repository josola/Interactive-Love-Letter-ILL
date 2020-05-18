/*
 * Determines capabilites of handmaid card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef HANDMAID_h
#define HANDMAID_h

#include "card.h"

class Handmaid : public Card
{
public:
	Handmaid(const string name, const int value);
	~Handmaid();

private:

};

Handmaid::Handmaid(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

Handmaid::~Handmaid()
{
}

#endif // !HANDMAID_h
