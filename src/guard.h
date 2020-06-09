/*
 * guard.h
 * determines capabilites of guard card
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
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
