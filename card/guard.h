/*
 * Determines capabilites of guard card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef GUARD_h
#define GUARD_h

#include "card.h"

class Guard : public Card
{
public:
	Guard(const string name, const int value);

    void Action();

private:

};

#endif // !GUARD_h
