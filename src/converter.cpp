/*
 * Implementation for the data converter.
 * (c) 2019-2021 Jordan sola. All rights reserved. (MIt License)
 * Written by Jordan Sola 2019-2021
 */

#include <cassert>

#include "converter.hpp"
#include "admirer.hpp"
#include "game_state.hpp"

Admirer* Converter::NumPlayer(int num, GameState& state) {
	
	assert(num >= 1 && num <= 6);

	Admirer* output = nullptr;

	for (Admirer& iPlayer : state.admirers_) {
		if (iPlayer.GetValue() == num)
			output = &iPlayer;
	}
	
	return output;
	
}
