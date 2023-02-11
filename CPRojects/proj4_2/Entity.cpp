/*****************************************
** File:    Entity.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/10/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Entity.h.
*/

#include "Entity.h"

Entity::Entity() {
    m_name = "entity";
}

Entity::Entity(string name) : m_name(name){}

Entity::~Entity() {}

string Entity::GetName() { return m_name; }

void Entity::SetName(string name){ m_name = name; }




