/*
 * Determines capabilites of countess card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef COUNTESS_h
#define COUNTESS_h

#include "card.h"

class Countess : public Card
{
public:
	Countess(const string name, const int value);

    void Action();

private:

};

#endif // !COUNTESS_h
