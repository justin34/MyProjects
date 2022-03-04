/*****************************************
** File:    Mario.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/15/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Mario.h.
*/

#include "Mario.h"

Mario::Mario() : Character(){}

Mario::Mario(string name, double topSpeed, double handling, double acceleration) :
        Character(name, topSpeed, handling,acceleration){

}

Mario::~Mario() {
}

string Mario::GetType() {
    return "Mario";
}

void Mario::SpecialMove() {
    cout << "lol you thought" << endl;
}

ostream &Mario::operator<<(ostream & sout) {
    sout << "Mario (" << GetName() << ") has gone " << Character::GetCurLocation() << " meters and is currently going " <<
         Character::GetCurSpeed() << "m/s.";

    return sout;
}