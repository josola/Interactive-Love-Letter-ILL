/*
 * handmaid.h
 * determines capabilites of handmaid card
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef HANDMAID_h
#define HANDMAID_h

#include "card.h"

class Handmaid : public Card
{
public:
	Handmaid(const string name, const int value);

    void Action();

private:

};

#endif // !HANDMAID_h
