/*
 * chancellor.h
 * determines capabilites of chancellor card
 * this software uses the MIT license.
 * written by Jordan Sola 2019-2020
 */

#ifndef CHANCELLOR_h
#define CHANCELLOR_h

#include "card.h"

class Chancellor : public Card
{
public:
	Chancellor(const string name, const int value);

    void Action();

private:

};

#endif // !CHANCELLOR_h
