/*****************************************
** File:    Wario.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/15/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Wario.h.
*/

#include "Wario.h"

Wario::Wario() : Character(){}

Wario::Wario(string name, double topSpeed, double handling, double acceleration) :
        Character(name, topSpeed, handling,acceleration){

}

Wario::~Wario() {
}

string Wario::GetType() {
    return "Wario";
}

void Wario::SpecialMove() {
    cout << "Wa WA WAAAAAA...... nothting" << endl;
}

ostream &Wario::operator<<(ostream & sout) {
    sout << "Wario (" << GetName() << ") has gone " << Character::GetCurLocation() << " meters and is currently going " <<
         Character::GetCurSpeed() << "m/s.";

    return sout;
}

