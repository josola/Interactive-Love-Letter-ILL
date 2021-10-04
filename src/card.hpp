/*
 * Defines the capabilities of the card class.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <vector>

class Card {
	
	public:
		Card(const std::string name = "", const int value = 0, const std::string description = "");
		const std::string GetName() const;
		const std::string GetDescription() const;
		const int GetValue() const;
		void PrintName() const;
		void PrintValue() const;
		void PrintDescription() const;

	protected:
		std::string name_ = "";
		std::string description_ = "";
		int value_ = 0;
	
};

#endif // !CARD_HPP
