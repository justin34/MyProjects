/*****************************************
** File:    Item.cpp
** Project: CMSC 202 Project 3, Fall 2021
** Author:  Jabril Hall
** Date:    10/24/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Item.h.
*/

#include "Item.h"

Item::Item() {
    m_name = "none";
    m_time = 0;
    m_next = nullptr;
}

Item::Item(string name, int time) {
    m_name = name;
    m_time = time;
    m_next = nullptr;
}

// getters/setters


void Item::SetName(string name) {
    m_name = name;
}

string Item::GetName() {
    return m_name;
}

Item *Item::GetNext() {
    return m_next;
}

void Item::SetNext(Item *next) {
    m_next = next;
}

int Item::GetTime() {
    return m_time;
}

void Item::SetTime(int time) {
    m_time = time;
}