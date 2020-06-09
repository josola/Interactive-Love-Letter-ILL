/*
 * card.cpp
 * implementation for card.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include "card.h"

Card::Card(const string name, const int value) : name_(name), value_(value) {};

const string Card::GetName()
{
    return name_;
}
const int Card::GetValue()
{
    return value_;
}