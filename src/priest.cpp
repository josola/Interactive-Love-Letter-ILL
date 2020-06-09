/*
 * priest.h
 * implementation for priest.cpp
 * this software uses the MIT license.
 * written by Jordan Sola 2019-2020
 */

#include "priest.h"

Priest::Priest(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

void Priest::Action()
{
}