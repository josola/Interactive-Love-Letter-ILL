/*
 * Implementation for the card class.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <iostream>

#include "card.hpp"

Card::Card(const std::string name, const int value, const std::string description) : name_(name), value_(value), description_(description) {};

const std::string Card::GetName() const {
	return name_;
}

const std::string Card::GetDescription() const {
	return description_;
}

const int Card::GetValue() const {
	return value_;
}

void Card::PrintName() const {
	std::cout << name_;
}

void Card::PrintValue() const {
	std::cout << value_;
}

void Card::PrintDescription() const {
	std::cout << description_;
}
