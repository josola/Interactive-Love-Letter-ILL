/*
 * Implementation for support capabilities for input functions.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <cassert>
#include <iostream>

#include "input.hpp"
#include "game_state.hpp"
#include "admirer.hpp"

const bool CheckCard(const int card) {
	
	if (card < 0 || card > 9 || std::cin.fail())
		return false;
	else
		return true;
	
}

void FixCard(int &card) {
	
	while (card < 0 || card > 9 || std::cin.fail()) {
		
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		
		std::cout << "Card must be between 0 and 9." << std::endl;
		std::cin >> card;
		
	}
	
}

void SanitizeCard(int &target, const int originator) {
	
	switch (originator) {
			
		case 1: {
			
			while (!CheckCard(target) || target == 1) {
				std::cout << "You cannot choose a Guard." << std::endl;
				FixCard(target);
			}
			
		}
		default: {
			while (!CheckCard(target))
				FixCard(target);
		}
			
	}
	
}

const bool CheckTarget(const int input, const GameState &state) {
	
	if (input < 1 || input > state.admirers_.size() || std::cin.fail())
		return false;
	else
		return true;
	
}

void FixTarget(int &input, const GameState &state) {
	
	while (input < 1 || input > state.admirers_.size()) {
		
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		
		std::cout << "Number must be between 1 and " << state.admirers_.size() << std::endl;
		std::cin >> input;
		
	}
	
}

void SanitizeTarget(int &target, const GameState &state, const int card, Admirer *aggressor) {
	
	assert(card >= 0 && card <= 9);
	
	bool good_target = false;
	while (!good_target) {
		
		if (!CheckTarget(target, state))
			FixTarget(target, state);
		else
			good_target = true;
		
	}
	
}

const bool OpponentsProtected(Admirer *aggressor, GameState &state) {
	
	int protected_count = 0;
	for (Admirer &iPlayer : state.admirers_) {
		if (iPlayer.ProtectionStatus() && (iPlayer.GetValue() != aggressor->GetValue()))
			protected_count++;
	}
	
	if (protected_count == state.admirers_.size() - 1)
		return true;
	else
		return false;
	
}

Admirer *GetTarget(Admirer *aggressor, GameState &state, const int card) {
	
	assert(card >= 0 && card <= 9);
	
	Admirer *target_player = nullptr;
	
	bool protected_target = true;
	while (protected_target) {
		
		std::cout << aggressor->GetName() << " choose a target admirer: ";
		
		int target = 0;
		std::cin >> target;
		SanitizeTarget(target, state, card, aggressor);
		
		target_player = aggressor->GetConversion()->NumPlayer(target, state);
		
		if (target_player->ProtectionStatus() && (target_player->GetValue() != aggressor->GetValue()))
			std::cout << target_player->GetName() << " has Handmaid protection." << std::endl;
		else if (!target_player->Status())
			std::cout << target_player->GetName() << " is out." << std::endl;
		else if (card != 5 && (target_player->GetValue() == aggressor->GetValue()))
			std::cout << "You cannot choose yourself." << std::endl;
		else
			protected_target = false;
		
	}
	
	return target_player;
	
}

const bool CheckCharacter(const char input, const char target) {
	
	if (input == target)
		return true;
	else
		return false;
	
}

void FixCharacter(char &input, const char target) {
	
	while (input != target) {
		
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		
		std::cout << "Input must be '" << target << std::endl;
		std::cin >> input;
		
	}
	
}

void SanitizeCharacter(char &input, const char target) {
	while (!CheckCharacter(input, target))
		FixCharacter(input, target);
}
