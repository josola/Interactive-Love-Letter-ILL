#include "converter.h"
#include "admirer.hpp"
#include "game_state.h"

#include <cassert>

Admirer* Converter::NumPlayer(int num, GameState& state)
{
	assert(num >= 1 && num <= 6);

	Admirer* output = nullptr;

	for (Admirer& iPlayer : state.admirers_)
	{
		if (iPlayer.GetValue() == num)
		{
			output = &iPlayer;
		}
	}
	return output;
}