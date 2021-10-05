/*
 * Defines the data converter's abilities.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <vector>

class Admirer;
class GameState;

struct Converter{
	
	Admirer* NumPlayer(int num, GameState& state);
	
};

#endif // !CONVERTER_HPP
