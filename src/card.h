/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

struct Card
{
public:
    const string GetName();
    const int GetValue();

    void SetName(const string name);
    void SetValue(const int value);

private:
    string name_ = " ";
    int value_ = 0;
};

#endif // !CARD_h