/*
 * Implementation for the admirer class.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "admirer.hpp"
#include "deck.hpp"
#include "card.hpp"

Admirer::Admirer(const string name, const int value, const Reference &reference) : name_(name), value_(value), reference_(reference) {};

const bool Admirer::ProtectionStatus() const {
	return handmaid_;
}

const string Admirer::GetName() const {
	return name_;
}

std::vector<Card>* Admirer::GetHand() {
	return &hand_;
}

const bool Admirer::Status() const {
	return playing_;
}

const int Admirer::GetValue() const {
	return value_;
}

const int Admirer::GetTokenCount() const {
	return token_count_;
}

const bool Admirer::HasEmissaryBonus() const {
	return spy_;
}

Converter *Admirer::GetConversion() {
	return &convert_;
}

const bool Admirer::Starting() const {
	return starting_;
}

void Admirer::Draw(const Card obj) {
	hand_.push_back(obj);
}

void Admirer::SetProtection(const bool state) {
	handmaid_ = state;
}

void Admirer::GainEmissaryBonus() {
	spy_ = true;
}

void Admirer::Reset() {

	hand_.clear();
	handmaid_ = false;
	spy_ = false;
	playing_ = true;

}

void Admirer::Discard(const int choice, std::vector<Card> &deck) {

	for (Card &iCard : hand_) {

		if (iCard.GetValue() == choice) {

			deck.push_back(iCard);
			RemoveCard(iCard.GetValue());

			break;

		}

	}

}

void Admirer::DiscardHand(std::vector<Card> &deck) {
	for (Card &iCard : hand_)
		Discard(iCard.GetValue(), deck);
}

void Admirer::Addtoken() {
	token_count_++;
}

void Admirer::Winner(const bool state) {
	winner_ = state;
}

void Admirer::RemoveCard(const int card) {

	for (size_t i = 0; i < hand_.size(); i++) {

		if (hand_.at(i).GetValue() == card) {
			hand_.erase(hand_.begin() + i);
			break;
		}

	}

}

void Admirer::Out(std::vector<Card> &deck) {

	this->DiscardHand(deck);
	this->Reset();
	this->playing_ = false;

}

void Admirer::SetStarting(const bool state) {
	starting_ = state;
}

void Admirer::PrintHand() const {

	std::cout << std::endl << this->GetName() << " hand:" << std::endl;

	if (!hand_.empty()) {

		for (size_t i = 0; i < hand_.size(); i++) {

			if (i < hand_.size() - 1)
				std::cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << ", ";
			else
				std::cout << hand_.at(i).GetValue() << '-' << hand_.at(i).GetName() << std::endl << std::endl;
				
		}

	}
	else
		std::cout << "EMPTY\n";

}
