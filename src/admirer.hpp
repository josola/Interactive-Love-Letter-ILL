/*
 * Defines the capabilities of the Admirer class.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#ifndef ADMIRER_HPP
#define ADMIRER_HPP

#include "converter.h"
#include "reference.h"

class Card;
class Reference;
class Token;
class Deck;
class InputCheck;
class Deck;

class Admirer {

	public:

		Admirer(const string name, const int value, const Reference &reference);

		// getters
		const bool ProtectionStatus() const;
		const string GetName() const;
		vector<Card>* GetHand();
		const bool Status() const;
		const int GetValue() const;
		const int GetTokenCount() const;
		const bool HasEmissaryBonus() const;
		Converter* GetConversion();
		const bool Starting() const;

		// setters
		void Draw(const Card obj);
		void GainEmissaryBonus();
		void Reset();
		void SetProtection(const bool state);
		void Discard(const int choice, vector<Card> &deck);
		void DiscardHand(vector<Card> &deck);
		void Addtoken();
		void Winner(const bool state);
		void RemoveCard(const int card);
		void Out(vector<Card> &deck);
		void SetStarting(const bool state);

		// printer
		void PrintHand() const;

	private:

		// information
		string name_ = "";
		int value_ = 0;

		// objects
		Reference reference_;
		vector<Card> hand_;
		int token_count_ = 0;

		// state
		bool handmaid_ = false;
		bool spy_ = false;
		bool playing_ = true;
		bool winner_ = false;
		bool starting_ = false;

		// data
		Converter convert_;

};

#endif // !ADMIRER_HPP
