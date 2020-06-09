/*
 * princess.cpp
 * implementation for princess.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include "princess.h"

Princess::Princess(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

void Princess::Action()
{
}