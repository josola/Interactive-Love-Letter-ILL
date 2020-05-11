
#include <string>
#include "spy.h"

using std::string;

Spy::Spy(string name, int value) : CardInterface{ name, value } {};

void Spy::Action(PlayerController& player)
{
	player.SetSpy(1);
}