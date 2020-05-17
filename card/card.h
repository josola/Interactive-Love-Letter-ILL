/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

class Card
{
public:
    Card(const string name = "DEFAULT CARD", const int value = -1);

    string GetName();
    int GetValue();
    virtual void Action() = 0;

private:
    string name_ = " ";
    int value_ = 0;
};

class CardController : public Card
{
public:
    CardController(const string name, const int value);

    CardController Builder(const int output);
    void Action();
};

#endif