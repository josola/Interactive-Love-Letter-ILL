/*
 * player.cpp
 * implementation for player.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include <algorithm>
#include <iterator>
#include "player.h"

using std::find;
using std::distance;

Player::Player(const string name, const int value) : name_(name), value_(value) {};

 //getters
const string Player::Name() {
	return name_;
}
const int Player::Value() {
	return value_;
}
const int Player::Guess() {
	return guess_;
}
const bool Player::Current() {
	return current_;
}
const bool Player::Spy() {
	return spy_;
}
const bool Player::Winner() {
	return winner_;
}
vector<Card> const Player::Hand() {
	return hand_;
}
const bool Player::Playing() {
	return playing_;
}
const int Player::Tokens() {
	return token_count_;
}

//setters
void Player::SetName(const string name) {
	name_ = name;
}
void Player::SetValue(const int value) {
	value_ = value;
}
void Player::SetCurrent(const bool value) {
	current_ = value;
}
void Player::SetWinner(const bool value) {
	winner_ = value;
}
void Player::SetGuess(const int value) {
	guess_ = value;
}
void Player::SetPlaying(const bool value) {
	playing_ = value;
}
void Player::SetHandmaid(const bool value) {
	handmaid_ = value;
}
void Player::SetSpy(const bool value) {
	spy_ = value;
}


//action
void Player::InsertIntoHand(const Card& card) {
	hand_.push_back(card);
}
void Player::RemoveCardFromHand(const int value) {
	for (size_t i = 0; i < hand_.size(); i++) {
		if (hand_.at(i).GetValue() == value) {
			hand_.erase(hand_.begin() + i);
		}
	}
}
void Player::ClearHand() {
	hand_.erase(hand_.begin(), hand_.end());
}

//actions
Card Player::DrawCard(Deck& deck) {
	Card top_card = deck.GetCard(0);
	return top_card;
}