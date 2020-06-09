/*
 * spy.cpp
 * implementation for spy.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include <string>
#include "spy.h"

using std::string;

Spy::Spy(const string name, const int value) : Card{ name, value } {};

void Spy::Action(Player &player)
{
	player.SetSpy(1);
}