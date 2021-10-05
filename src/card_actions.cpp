/*
 * Implementation for the card actions.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <iostream>
#include <algorithm>
#include <cassert>

#include "card_actions.hpp"
#include "input.h"
#include "game_state.h"
#include "admirer.hpp"
#include "deck.hpp"

void Emissary(Admirer *player) {
	assert(!player->HasEmissaryBonus());
	player->GainEmissaryBonus();
}

void Defender(GameState &state, Admirer *aggressor, vector<Card> &deck) {
	
	if (OpponentsProtected(aggressor, state)) {
		std::cout << "All players have Damsel protection!" << std::endl;
		return;
	}
	
	Admirer *target = GetTarget(aggressor, state, 1);
	
	std::cout << aggressor->GetName() << " guess a card: ";
	
	int card = 0;
	std::cin >> card;
	SanitizeCard(card, 1);
	
	for (const Card &iCard : *target->GetHand()) {
		
		if (iCard.GetValue() == card) {
			
			std::cout << "Match!" << std::endl;
			target->Out(deck);
			
			return;
			
		}
		
	}
	
	std::cout << "No match!" << std::endl;
	
}

void Cleric(GameState &state, Admirer *aggressor) {
	
	if (OpponentsProtected(aggressor, state)) {
		std::cout << "All players have Damsel protection!" << std::endl;
		return;
	}
	
	Admirer *target = GetTarget(aggressor, state, 2);
	
	target->PrintHand();
	
}

void Lord(GameState &state, Admirer *aggressor, vector<Card> &deck) {
	
	if (OpponentsProtected(aggressor, state)) {
		std::cout << "All players have Damsel protection!" << std::endl;
		return;
	}
	
	Admirer *target = GetTarget(aggressor, state, 3);
	
	vector<Card>* target_hand = target->GetHand();
	vector<Card>* aggressor_hand = aggressor->GetHand();
	
	if (aggressor_hand->at(0).GetValue() > target_hand->at(0).GetValue()) {
		std::cout << aggressor->GetName() << " had the higher card!" << std::endl;
		target->Out(deck);
	}
	else if (aggressor_hand->at(0).GetValue() == target_hand->at(0).GetValue())
		std::cout << "Admirers hand the same card!" << std::endl;
	else {
		std::cout << target->GetName() << " had the higher card!" << std::endl;
		aggressor->Out(deck);
	}
	
}

void Damsel(Admirer *player) {
	assert(!player->ProtectionStatus());
	player->SetProtection(1);
}

void Archduke(GameState &state, Admirer *aggressor, vector<Card> &deck) {
	
	if (OpponentsProtected(aggressor, state)) {
		
		std::cout << "All players have Damsel protection!" << std::endl;
		std::cout << "Archduke applies to you!" << std::endl;
		
		vector<Card> *hand = aggressor->GetHand();
		
		if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
			GrandDuchess(aggressor, deck);
		else {
			
			aggressor->DiscardHand(deck);
			aggressor->Draw(deck.at(0));
			deck.erase(deck.begin() + 0);
			
		}
		
		return;
		
	}
	
	Admirer *target = GetTarget(aggressor, state, 5);
	
	if (target->GetValue() == aggressor->GetValue()) {
		
		std::cout << "You chose yourself!" << std::endl;
		std::cout << "Please discard your hand (d): ";
		
		char discard = ' ';
		std::cin >> discard;
		SanitizeCharacter(discard, 'd');
		
		vector<Card> *hand = aggressor->GetHand();
		
		if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
			GrandDuchess(aggressor, deck);
		else {
			
			aggressor->DiscardHand(deck);
			aggressor->Draw(deck.at(0));
			deck.erase(deck.begin() + 0);
			
		}
		
	}
	else {
		
		std::cout << target->GetName() << " discards their hand!" << std::endl;
		
		vector<Card> *hand = target->GetHand();
		
		if (any_of(hand->begin(), hand->end(), [](const Card &iCard) { return iCard.GetValue() == 9; }))
			GrandDuchess(target, deck);
		else {
			
			target->DiscardHand(deck);
			target->Draw(deck.at(0));
			deck.erase(deck.begin() + 0);
			
		}
		
	}
	
}

void Adjudicator(vector<Card> &deck, Admirer *player) {
	
	std::cout << player->GetName() << " draw two cards (d): ";
	
	char draw = ' ';
	std::cin >> draw;
	SanitizeCharacter(draw, 'd');
	
	for (int i = 0; i < 2; i++)
		player->Draw(deck.at(0));
	
	player->PrintHand();
	
	std::cout << "First card to put back: ";
	
	int first = 0;
	std::cin >> first;
	SanitizeCard(first, 6);
	
	if (first == 9)
		GrandDuchess(player, deck);
	else
		player->Discard(first, deck);
	
	std::cout << "Second card to put back: ";
	
	int second = 0;
	std::cin >> second;
	SanitizeCard(second, 6);
	
	if (second == 9)
		GrandDuchess(player, deck);
	else
		player->Discard(second, deck);
	
}

void Emperor(GameState &state, Admirer *aggressor) {
	
	if (OpponentsProtected(aggressor, state)) {
		std::cout << "All players have Damsel protection!" << std::endl;
		return;
	}
	
	Admirer *target = GetTarget(aggressor, state, 7);
	
	std::cout << target->GetName() << " trade hands with " << aggressor->GetName() << std::endl;
	
	vector<Card> *instigator_hand = aggressor->GetHand();
	vector<Card> *target_hand = target->GetHand();
	
	swap(*instigator_hand, *target_hand);
	
	aggressor->PrintHand();
}

void Duchess(Admirer *player) {
	std::cout << player->GetName() << " has played the Duchess!" << std::endl;
}

void GrandDuchess(Admirer *player, vector<Card> &deck) {
	std::cout << player->GetName() << " had the GrandDuchess!" << std::endl;
	player->Out(deck);
}
