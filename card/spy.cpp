
#include <string>
#include "spy.h"

using std::string;

Spy::Spy(const string name, const int value) : Card{ name, value } {};

void Spy::Action(PlayerController& player)
{
	player.SetSpy(1);
}