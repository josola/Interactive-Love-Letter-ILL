/*
 * Defines support capabilities for input functions.
 * (c) 2019-2021 Jordan Sola. All rights reserved. (MIT License)
 * Written by Jordan Sola 2019-2021
 */

class GameState;
class Admirer;

const bool CheckCard(const int card);
void FixCard(int &card);
void SanitizeCard(int &target, const int originator);

const bool CheckTarget(const int input, const GameState &state);
void FixTarget(int &input, const GameState &state);
void SanitizeTarget(int &target, const GameState &state, const int card, Admirer *aggressor);

const bool OpponentsProtected(Admirer *aggressor, GameState &state);
Admirer *GetTarget(Admirer *aggressor, GameState &state, const int card);

const bool CheckCharacter(const char input, const char target);
void FixCharacter(char &input, const char target);
void SanitizeCharacter(char &input, const char target);
