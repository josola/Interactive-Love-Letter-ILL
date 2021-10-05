/*
 * Defines the game state.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <vector>

class Admirer;

struct GameState {
	
	void InsertPlayer(Admirer admirer);
	void SetPlayers(int count);

	std::vector<Admirer> admirers_;
	int winning_token_count_ = 0;
	int round_count_ = 1;
	
};

#endif // !GAME_STATE_HPP
