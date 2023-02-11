/*****************************************
** File:    Toad.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/15/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Toad.h.
*/


#include "Toad.h"

Toad::Toad() : Character() {

}

Toad::Toad(string name, double topSpeed, double handling, double acceleration) :
    Character(name, topSpeed, handling,acceleration){

}

Toad::~Toad() {
}

string Toad::GetType() {
    return "Toad";
}

void Toad::SpecialMove() {
    cout << "Toad farted" << endl;
}

ostream &Toad::operator<<(ostream & sout) {
    sout << "Toad (" << GetName() << ") has gone " << Character::GetCurLocation() << " meters and is currently going " <<
    Character::GetCurSpeed() << "m/s.";

    return sout;
}
