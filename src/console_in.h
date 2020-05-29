/*
 * Helper utility for console in.
 * This program uses the MIT license.
 * Written by Jordan Sola 2019-2020
 */

#ifndef CONSOLE_IN_h
#define CONSOLE_IN_h

class ConsoleIn
{
public:
    static int GetIntInput();
    static bool CorrectIntInput(const int input);
    static int FixIntInput();
    static void ClearInput();
    static char GatCharInput();
    static bool CorrectCharInput(const char input);
    static char FixCharInput();
};

#endif