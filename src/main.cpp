/*
 * Main point of execution for the Missive game.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <limits>

#include "deck.hpp"
#include "admirer.hpp"
#include "input.hpp"
#include "reference.hpp"
#include "game_state.hpp"
#include "card_actions.hpp"

int main() {
		
	std::cout << std::endl;
	
	std::cout << "-- WELCOME TO MISSIVE --" << std::endl;
	
	std::cout << std::endl;
	
	// Get starting admirer count
	int player_count = -1;
	while (player_count < 2 || player_count > 6) {
		
		std::cout << "How many admirers will be playing: ";
		
		std::cin >> player_count;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		
		if (player_count < 2 || player_count > 9)
			std::cout << "Number must be between 2 and 6 admirers:" << std::endl;
		
	}
	
	std::cout << std::endl;
	
	GameState gameState;
	gameState.SetPlayers(player_count);
	
	// Game loop
	bool game_over = false;
	while (!game_over) {
		
		// Main deck
		std::vector<Card> deck;
		Build(deck);
		Mix(deck);
		
		// Face up deck
		std::vector<Card> aside;
		aside.push_back(deck.at(0));
		deck.erase(deck.begin() + 0);
		
		// Discard deck
		std::vector<Card> discard;
		if (gameState.admirers_.size() == 2) {
			for (int i = 0; i < 2; i++) {
				discard.push_back(deck.at(0));
				deck.erase(deck.begin() + 0);
			}
		}
		
		// Deal starting hand
		for (Admirer &i : gameState.admirers_) {
			i.Draw(deck.at(0));
			deck.erase(deck.begin() + 0);
		}
		
		// Round count prompt
		std::cout << "-- ROUND " << gameState.round_count_ << " --" << std::endl;
		
		std::cout << std::endl;
		
		// --- Admirer turn ---
		
		std::vector<Admirer *> remaining_players;
		Admirer *winner = nullptr;
		
		bool end_round = false;
		while (!end_round) {
			
			for (size_t i = 0; i < gameState.admirers_.size(); i++) {
				
				// Set winner of previous round as starting admirer
				if (gameState.round_count_ > 1) {
					
					for (size_t j = 0; j < gameState.admirers_.size(); j++) {
						if (gameState.admirers_.at(j).Starting()) {
							i = j;
							gameState.admirers_.at(i).SetStarting(0);
						}
						
					}
					
				}
				
				// Access to admirer object during play
				Admirer *current_admirer = &gameState.admirers_.at(i);
				
				if (current_admirer->Status()) {
					
					current_admirer->SetProtection(0);
					
					// Draw input
					char draw = ' ';
					while (draw != 'd') {
						
						std::cout << current_admirer->GetName() << " draw a card (d): ";
						std::cin >> draw;
						
						if (std::cin.fail()) {
							std::cin.clear();
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						}
						
						if (draw != 'd')
							std::cout << "Input MUST be 'd':" << std::endl;
						
					}
					
					// Current admirer draw card
					// Current_player->Draw(deck.at(0));
					deck.erase(deck.begin() + 0);
					
					current_admirer->Draw(Card("HANDMAID", 4, "REF"));
					
					std::cout << std::endl;
					
					// Print game state
					std::cout << "Deck size:" << std::endl;
					std::cout << deck.size() << std::endl;
					
					std::cout << std::endl;
					
					std::cout << "Discard pile:" << std::endl;
					
					if (discard.empty())
						std::cout << "EMPTY" << std::endl;
					else {
						
						if (discard.size() == 1)
							std::cout << discard.at(0).GetName() << std::endl;
						else {
							
							for (size_t i = 0; i < discard.size(); i++) {
								
								if (i < discard.size() - 1)
									std::cout << discard.at(i).GetName() << ", ";
								else
									std::cout << discard.at(i).GetName() << std::endl;
							}
							
						}
						
					}
					
					std::cout << std::endl;
					
					std::cout << "Opponents:" << std::endl;
					
					for (size_t i = 0; i < gameState.admirers_.size(); i++) {
						
						if (gameState.admirers_.at(i).Status()) {
							
							if (gameState.admirers_.size() == 2 && gameState.admirers_.at(i).GetValue() != current_admirer->GetValue())
								std::cout << gameState.admirers_.at(i).GetName() << std::endl;
							else {
								
								if (gameState.admirers_.at(i).GetValue() != current_admirer->GetValue()) {
									
									if (i == gameState.admirers_.size() - 1)
										std::cout << gameState.admirers_.at(i).GetName() << std::endl;
									else
										std::cout << gameState.admirers_.at(i).GetName() << ", ";
									
								}
								
							}
							
						}
						
					}
					
					std::cout << std::endl;
					
					std::cout << "Damsel protection:" << std::endl;
					
					bool players_have_damsel = any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.ProtectionStatus(); });
					if (players_have_damsel) {
						
						int damsel_count = count_if(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.ProtectionStatus(); });
						
						if (damsel_count == 1) {
							
							for (size_t i = 0; i < gameState.admirers_.size(); i++) {
								
								Admirer *damselPlayer = &gameState.admirers_.at(i);
								
								if (damselPlayer->ProtectionStatus() && (damselPlayer->GetValue() != current_admirer->GetValue())) {
									std::cout << damselPlayer->GetName() << std::endl;
									break;
								}
								
							}
							
						}
						else {
							
							int damsel_tally = 1;
							
							for (size_t i = 0; i < gameState.admirers_.size(); i++) {
								
								Admirer *iPlayer = &gameState.admirers_.at(i);
								
								if (iPlayer->ProtectionStatus() && (iPlayer->GetValue() != current_admirer->GetValue())) {
									
									if (damsel_tally != damsel_count)
										std::cout << iPlayer->GetName() << ", ";
									else
										std::cout << iPlayer->GetName() << std::endl;
									
									damsel_tally++;
									
								}
								
							}
							
						}
						
					}
					else
						std::cout << "NONE" << std::endl;
					
					std::cout << std::endl;
					
					std::cout << "Emissary Bonus:" << std::endl;
					
					bool players_have_emissary = any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.HasEmissaryBonus(); });
					
					if (players_have_emissary) {
						
						int emissary_count = count_if(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &i) { return i.HasEmissaryBonus(); });
						
						if (emissary_count == 1) {
							
							for (size_t i = 0; i < gameState.admirers_.size(); i++) {
								
								Admirer *emissaryPlayer = &gameState.admirers_.at(i);
								
								if (gameState.admirers_.at(i).HasEmissaryBonus()){
									std::cout << emissaryPlayer->GetName() << std::endl;
									break;
								}
								
							}
							
						}
						else {
							
							int emissary_tally = 1;
							for (size_t i = 0; i < gameState.admirers_.size(); i++){

								Admirer *iPlayer = &gameState.admirers_.at(i);

								if (iPlayer->GetValue() != current_admirer->GetValue() && iPlayer->HasEmissaryBonus()) {

									if (emissary_tally == 1) {
										std::cout << iPlayer->GetName() << ", ";
										emissary_tally++;
									}
									else
										std::cout << iPlayer->GetName() << std::endl;
								}

							}

						}

					}
					else
						std::cout << "NONE" << std::endl;
					
					current_admirer->PrintHand();
					
					// Log cards already in hand
					std::vector<int> in_hand;
					for (Card iCard : *current_admirer->GetHand())
						in_hand.push_back(iCard.GetValue());
					
					// Duchess restriction check
					bool duchess = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 8; });
					bool emperor = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 7; });
					bool archduke = any_of(in_hand.begin(), in_hand.end(), [](int i) { return i == 5; });
					
					bool correct_input = false;
					int card = 0;
					while (!correct_input) {

						std::cout << current_admirer->GetName() << " play a card: ";
						std::cin >> card;

						SanitizeCard(card, -1);
						
						if ((duchess && emperor) || (duchess && archduke)) {

							if (std::cin.fail()) {
								std::cin.clear();
								std::cin.ignore(1000, '\n');
							}

							std::cout << "You MUST play the Duchess." << std::endl;

						}
						else {

							for (Card &iCard : *current_admirer->GetHand()) {

								if (iCard.GetValue() == card) {
									correct_input = true;
									break;
								}

							}
							if (!correct_input)
								std::cout << "Not in hand." << std::endl;
						}

					}
					
					// Discard card
					current_admirer->Discard(card, discard);
					
					// Play card action
					switch (card) {

						case 0:
							Emissary(current_admirer);
							break;

						case 1:
							Defender(gameState, current_admirer, discard);
							break;

						case 2:
							Cleric(gameState, current_admirer);
							break;

						case 3:
							Lord(gameState, current_admirer, discard);
							break;

						case 4:
							Damsel(current_admirer);
							break;

						case 5:
							Archduke(gameState, current_admirer, discard);
							break;

						case 6:
							Adjudicator(discard, current_admirer);
							break;

						case 7:
							Emperor(gameState, current_admirer);
							break;

						case 8:
							Duchess(current_admirer);
							break;

						case 9:
							GrandDuchess(current_admirer, discard);
							break;

					}

					std::cout << std::endl;

				}
				
				// Reset remaining admirers, so as not to stack remainders
				remaining_players.erase(remaining_players.begin(), remaining_players.end());
				
				// Check how many standing admirers
				for (Admirer &iPlayer : gameState.admirers_) {
					if (iPlayer.Status())
						remaining_players.push_back(&iPlayer);
				}
				
				// Round end check
				if (deck.empty() || remaining_players.size() == 1) {
					end_round = true;
					break;
				}

			}

		}
		
		// Increase round count
		gameState.round_count_ += 1;
		
		// --- Round end ---
		
		// Deck is empty, admirers compare hands, highest hand wins the round
		if (deck.size() == 0) {

			std::cout << "Deck is empty, admirers compare hands!" << std::endl;

			for (size_t i = 0; i < gameState.admirers_.size(); i++) {

				Admirer *iPlayer = &gameState.admirers_.at(i);
				
				if (i < gameState.admirers_.size() - 1) {
					if (iPlayer->GetHand()->at(0).GetValue() > gameState.admirers_.at(i + 1).GetHand()->at(0).GetValue())
						winner = &gameState.admirers_.at(i);
				}

			}

			std::cout << winner->GetName() << " has the highest hand! " << winner->GetHand()->at(0).GetName() << std::endl;
			
			winner->Addtoken();
			winner->Winner(1);
		
		}
		
		// Emissary bonus
		int emissary_count = 0;
		if (any_of(gameState.admirers_.begin(), gameState.admirers_.end(), [](Admirer &iPlayer) { return iPlayer.HasEmissaryBonus(); })) {

			Admirer *emissary_bonus = nullptr;
			
			for (Admirer &iPlayer : gameState.admirers_) {

				if (iPlayer.Status() && iPlayer.HasEmissaryBonus() && emissary_count < 2) {
					emissary_bonus = &iPlayer;
					emissary_count++;
				}

			}
			if (emissary_count >= 2)
				std::cout << "Multiple admirers had the Emissary, no one gets a bonus" << std::endl;
			else if (emissary_count == 1){

				std::cout << emissary_bonus->GetName() << " had the Emissary!" << std::endl;
				emissary_bonus->Addtoken();
				std::cout << emissary_bonus->GetName() << " token count: " << emissary_bonus->GetTokenCount() << std::endl;
			
			}

		}
		
		// Celebrate the last admirer standing
		for (Admirer &iPlayer : gameState.admirers_) {
			if (iPlayer.Status())
				winner = &iPlayer;
		}
		
		std::cout << winner->GetName() << " was the last admirer standing!" << std::endl;

		winner->Addtoken();
		
		std::cout << std::endl;

		std::cout << winner->GetName() << " token count: " << winner->GetTokenCount() << std::endl;
		
		winner->SetStarting(1);
		
		// Set admirers to base
		if (gameState.round_count_ > 1) {
			for (Admirer &i : gameState.admirers_)
				i.Reset();
		}
		
		// Check that admirer has winning token count
		for (Admirer &iPlayer : gameState.admirers_) {

			if (iPlayer.GetTokenCount() == gameState.winning_token_count_) {

				std::cout << iPlayer.GetName() << " has " << iPlayer.GetTokenCount() << " tokens!" << std::endl;
				std::cout << iPlayer.GetName() << " wins the game!" << std::endl;

				game_over = true;
				
				break;
			}

		}

	}
	
	return 0;
}
