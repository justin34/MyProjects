/*****************************************
** File:    Obstacle.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/17/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Obstacle.h.
*/

#include "Obstacle.h"

Obstacle::Obstacle() {
    m_color = "null";
}

Obstacle::Obstacle(string color) {
    m_color = color;
}

Obstacle::~Obstacle() {}

void Obstacle::SetColor(string color) {
    m_color = color;
}

string Obstacle::GetColor() {
    return m_color;
}



