/*
 * countess.cpp
 * implementation for countess.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include "countess.h"

Countess::Countess(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

void Countess::Action()
{
}