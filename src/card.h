/*
 * card.h
 * determines card capabilities
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#ifndef CARD_h
#define CARD_h

#include <string>

using std::string;

struct Card
{
public:
    Card(const string name, const int value);

    const string GetName();
    const int GetValue();

private:
    string name_ = " ";
    int value_ = 0;
};

#endif // !CARD_h
