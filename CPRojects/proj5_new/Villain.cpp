/*****************************************
** File:    Villain.cpp
** Project: CMSC 202 Project 5, Fall 2021
** Author:  Jabril Hall
** Date:    12/6/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Villain.h.
*/

#include "Villain.h"

Villain::Villain() { // constructor1
    m_name = "";
    m_desc = "";
    m_rarity = 0;
    m_hp = 0;
    m_combat = 0;
}

Villain::Villain(string name, string desc, int hp, int combat, int rarity) { // constructor2
    m_name = name;
    m_desc = desc;
    m_hp = hp;
    m_combat = combat;
    m_rarity = rarity;
}

void Villain::Attack() {
    cout << m_name << " attacks" << endl; // displays an attack message
}

// getters and setters

int Villain::GetCombat() {
    return m_combat;
}

string Villain::GetDesc() {
    return m_desc;
}

int Villain::GetHp() {
    return m_hp;
}

string Villain::GetName() {
    return m_name;
}

int Villain::GetRarity() {
    return m_rarity;
}

void Villain::SetCombat(int newCombat) {
    m_combat = newCombat;
}

void Villain::SetHp(int newHp) {
    if(newHp < 0)
        newHp = 0;
    m_hp = newHp;
}


ostream & operator<<(ostream& os, Villain& myVillain){
    os << myVillain.GetName() << "(hp:" << myVillain.GetHp() << " combat:" << myVillain.GetCombat() << ")";
    return os;
}
