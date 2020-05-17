/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "card.h"

/* Card Interface */

Card::Card(const string name, const int value) : name_(name), value_(value) {};

string Card::GetName() { return name_; }
int Card::GetValue() { return value_; }

/* Card Controller */

//constructor
CardController::CardController(const string name, const int value) : Card{ name, value } {};

//method(s)
CardController CardController::Builder(const int output)
{
    switch (output)
    {
    case 0:
    {
        CardController spyController("SPY[0]", 0);
        return spyController;
        break;
    }
    case 1:
    {
        CardController guardController("GUARD[1]", 1);
        return guardController;
        break;
    }
    case 2:
    {
        CardController priestController("PRIEST[2]", 2);
        return priestController;
        break;
    }
    case 3:
    {
        CardController baronController("BARON[3]", 3);
        return baronController;
        break;
    }
    case 4:
    {
        CardController handmaidController("HANDMAID[4]", 4);
        return handmaidController;
        break;
    }
    case 5:
    {
        CardController princeController("PRINCE[5]", 5);
        return princeController;
        break;
    }
    case 6:
    {
        CardController chancellorController("CHANCELLOR[6]", 6);
        return chancellorController;
        break;
    }
    case 7:
    {
        CardController kingController("KING[7]", 7);
        return kingController;
        break;
    }
    case 8:
    {
        CardController countessController("COUNTESS[8]", 8);
        return countessController;
        break;
    }
    case 9:
    {
        CardController princessController("PRINCESS[9]", 9);
        return princessController;
        break;
    }
    default:
        CardController ghostController("SHOULD NOT EXIST", -10);
        return ghostController;
        break;
    }
}

void CardController::Action()
{

}