/*
 * handmaid.cpp
 * implementation for handmaid.cpp
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include "handmaid.h"

Handmaid::Handmaid(const string name, const int value) : Card{}
{
    SetName(name);
    SetValue(value);
}

void Handmaid::Action()
{
}