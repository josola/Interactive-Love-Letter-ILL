/*
 * prince.cpp
 * implementation for prince.h
 * this software uses the MIT license
 * written by Jordan Sola 2019-2020
 */

#include "prince.h"

Prince::Prince(const string name, const int value) : Card{} {
    SetName(name);
    SetValue(value);
}

void Prince::Action() {

}