/*
 * Implementation for the gamestate.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include "game_state.hpp"
#include "reference.h"
#include "admirer.hpp"

#include <cassert>

void GameState::InsertPlayer(Admirer admirer) {
	admirers_.push_back(admirer);
}

void GameState::SetPlayers(int count) {
	
	Reference reference;
	
	switch (count) {
			
		case 2: {
			
			for (int i = 0; i < 2; i++) {
				std::string name = "ADMIRER[" + std::to_string(i + 1) + "]";
				InsertPlayer(Admirer(name, i + 1, reference));
			}
			
			winning_token_count_ = 6;
			
			break;
		}
		case 3: {
			
			for (int i = 0; i < 3; i++) {
				std::string name = "ADMIRER[" + std::to_string(i + 1) + "]";
				InsertPlayer(Admirer(name, i + 1, reference));
			}
			
			winning_token_count_ = 5;
			
			break;
		}
		case 4: {
			
			for (int i = 0; i < 4; i++) {
				std::string name = "ADMIRER[" + std::to_string(i + 1) + "]";
				InsertPlayer(Admirer(name, i + 1, reference));
			}
			
			winning_token_count_ = 4;
			
			break;
		}
		case 5: {
			
			for (int i = 0; i < 5; i++) {
				std::string name = "ADMIRER[" + std::to_string(i + 1) + "]";
				InsertPlayer(Admirer(name, i + 1, reference));
			}
			
			winning_token_count_ = 3;
			
			break;
		}
		case 6: {
			
			for (int i = 0; i < 6; i++) {
				std::string name = "ADMIRER[" + std::to_string(i + 1) + "]";
				InsertPlayer(Admirer(name, i + 1, reference));
			}
			
			winning_token_count_ = 3;
			
			break;
		}
	}
}
