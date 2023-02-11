/*****************************************
** File:    Character.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/10/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Character.h.
*/

#include "Character.h"


Character::Character() {

    // sets all members to 0 to avoid errors
    m_acceleration = 0;
    m_curLocation = 0;
    m_curSpeed = 0;
    m_handling = 0;
    m_topSpeed = 0;
}

Character::Character(string name, double topSpeed, double handling, double acceleration) : Entity(name),
    m_topSpeed(topSpeed), m_handling(handling), m_acceleration(acceleration) { // second constructor (also doing everything outside brackets now)
        m_curSpeed = 0;
        m_curLocation = 0;
    }

Character::~Character() {}

void Character::CalcSpeed(double gas) {
    m_curSpeed = m_acceleration * m_handling * gas; // finds the speed using the formula
    if (m_curSpeed > m_topSpeed) // checks if the speed is greater than the characters max speed
        m_curSpeed = m_topSpeed; // if it is it makes it drive at max speed
}

void Character::Tick(double maxSpeed) { // makes sure the current speed is not to fast for track
    if (m_curSpeed > maxSpeed){
        m_curSpeed = 0;
        cout << GetName() << " went to fast and crashed" << endl;
        return;
    }

    m_curLocation += m_curSpeed;
}

// getters and setters
double Character::GetAcceleration() {
    return m_acceleration;
}

double Character::GetCurLocation() {
    return m_curLocation;
}

double Character::GetCurSpeed() {
    return m_curSpeed;
}

double Character::GetHandling() {
    return m_handling;
}

double Character::GetTopSpeed() {
    return m_topSpeed;
}

void Character::SetCurLocation(double curlocation) {
    m_curLocation = curlocation;
}

void Character::SetCurSpeed(double curSpeed) {
    m_curSpeed = curSpeed;
}