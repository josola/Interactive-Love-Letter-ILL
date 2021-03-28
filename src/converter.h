//===-- converter.h - Functions that convert input into data ----*- C++ -*-===//
//
// This software uses the MIT license.
// See https://mit-license.org/ for license information.
//
//===----------------------------------------------------------------------===//
///
/// This file determines functions that convert input data into other forms.
///
//===----------------------------------------------------------------------===//

#ifndef CONVERTER_h
#define CONVERTER_h

#include <vector>

class Admirer;
class GameState;

using std::vector;

struct Converter
{
	Admirer* NumPlayer(int num, GameState& state);
};

#endif // !CONVERTER_h
