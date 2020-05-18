/*
 * Helper utility for card.
 * This software uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#include "card.h"

/* Card Interface */

string Card::GetName()
{
    return name_;
}
int Card::GetValue()
{
    return value_;
}

void Card::SetName(const string name)
{
    name_ = name;
}
void Card::SetValue(const int value)
{
    value_ = value;
}