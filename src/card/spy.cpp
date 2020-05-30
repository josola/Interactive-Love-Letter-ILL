
#include <string>
#include "spy.h"

using std::string;

Spy::Spy(const string name, const int value) : Card{} {
	SetName(name);
	SetValue(value);
}

void Spy::Action(Player& player) {
	player.SetSpy(1);
}