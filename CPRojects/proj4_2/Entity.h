/***********************************************************
 ** File:    Entity.h
 ** Project: UMBC Mario Kart
 ** Author:  Jeremy Dixon
 ** Date     11/1/2021
 ** Section: N/A
 ** This file contains the header file of the Entity class
 **********************************************************/
#ifndef ENTITY_H_
#define ENTITY_H_
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

//Parent class for all characters and obstacles
class Entity {
 public:
  // Name: Entity() - Default Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes (not specifically used)
  Entity();
  // Name: Entity(string) - Overloaded Constructor
  // Description: Abstract class - cannot directly instantiate this class
  // Preconditions: None
  // Postconditions: Populates variables used in child classes
  Entity(string);
  // Name: virtual ~Entity - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  virtual ~Entity();
  // Name: GetName()
  // Description: Returns name of entity
  // Preconditions: Entity has name
  // Postconditions: None
  string GetName();
  // Name: SetName()
  // Description: Sets name of entity
  // Preconditions: None
  // Postconditions: Name is set
  void SetName(string);
  // Purely virtual functions defined in Character, Mario, Wario, or Toad
  virtual string GetType() = 0;
  virtual double GetCurLocation() = 0;
  virtual void SetCurLocation(double) = 0;
  virtual double GetCurSpeed() = 0;
  virtual void SetCurSpeed(double) = 0;
  virtual double GetTopSpeed() = 0;
  virtual double GetHandling() = 0;
  virtual double GetAcceleration() = 0;
  virtual void Tick(double) = 0;
  virtual void SpecialMove() = 0;
  virtual void CalcSpeed(double) = 0;
  virtual ostream& operator<<(ostream& os) = 0;
private:
  string m_name; //Name of entity
};

#endif
