/*
 * Defines the reference card.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

#include <iostream>

#include "reference.hpp"

Reference::Reference() : Card{"REFERENCE", -1} {};

void Reference::Print() {
	for (std::string i : reference)
		std::cout << i << std::endl;
}
