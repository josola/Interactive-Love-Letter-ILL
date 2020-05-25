/*
 * Determines capabilites of priest card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef PRIEST_h
#define PRIEST_h

#include "card.h"

class Priest : public Card
{
public:
	Priest(const string name, const int value);

    void Action();

private:

};

#endif // !PRIEST_h
