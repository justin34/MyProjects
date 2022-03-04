/*****************************************
** File:    Hero.cpp
** Project: CMSC 202 Project 5, Fall 2021
** Author:  Jabril Hall
** Date:    12/6/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Hero.h.
*/


#include "Hero.h"

using namespace std;

Hero::Hero() {
    m_name = "";
    m_desc = "";
    m_rarity = 0;
    m_hp = 0;
    m_combat = 0;
}

Hero::Hero(string name, string desc, int hp, int combat, int rarity) {
    m_name = name;
    m_desc = desc;
    m_combat = combat;
    m_hp = hp;
    m_rarity = rarity;
}

void Hero::Train() { // raises combat by 10 and ouptputs it
    m_combat+=10;
    cout << m_name << "'s combat has raised to " << m_combat << endl;
}

void Hero::Attack() { // displays an attack message
    cout << m_name << " attacks" << endl;
}

// getters and setters
int Hero::GetCombat() {
    return m_combat;
}

string Hero::GetDesc() {
    return m_desc;
}

int Hero::GetHp() {
    return m_hp;
}

string Hero::GetName() {
    return m_name;
}

int Hero::GetRarity() {
    return m_rarity;
}

void Hero::SetCombat(int newCombat) {
    m_combat = newCombat;
}

void Hero::SetHp(int newHp) {
    if(newHp < 0)
        newHp = 0;
    m_hp = newHp;
}



ostream& operator<< (ostream& os, Hero &myHero){
    os << myHero.GetName() << "(hp:" << myHero.GetHp() << " combat:" << myHero.GetCombat() << ")";
    return os;
}


