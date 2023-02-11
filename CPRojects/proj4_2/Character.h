/***********************************************************
 ** File:    Character.h
 ** Project: UMBC Mario Kart
 ** Author:  Jeremy Dixon
 ** Date     11/1/2021
 ** Section: N/A
 ** This file contains the header file of the Character class
***********************************************************/
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "Entity.h"

class Character: public Entity {
 public:
  // Name: Character() - Default Constructor
  // Description: Creates a new character
  // Preconditions: None
  // Postconditions: Can create a character
  Character();
  // Name: Character(string name) - Overloaded constructor
  // Description: Creates a new character (name, top speed, handling, acceleration)
  // Preconditions: None
  // Postconditions: Can be used to populate character or child classes
  Character(string, double, double, double);
  // Name: ~Character - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  ~Character();
  // Name: GetType
  // Description: Purely virtual function defined in child classes
  // Precondition: None
  // Postcondition: Must be populated in child classes
  virtual string GetType() = 0;
  // Name: GetCurLocation()
  // Description: Returns m_curLocation
  // Precondition: Must be populated
  // Postcondition: Returns m_curLocation (how far down the track has the racer gone)
  virtual double GetCurLocation();
  // Name: SetCurLocation()
  // Description: Sets m_curLocation
  // Precondition: None
  // Postcondition: Sets m_curLocation (how far down the track has the racer gone)
  virtual void SetCurLocation(double);
  // Name: GetCurSpeed()
  // Description: Returns m_curSpeed
  // Precondition: Must be populated
  // Postcondition: Returns m_curSpeed (how fast the racer is going)
  virtual double GetCurSpeed();
  // Name: SetCurSpeed()
  // Description: Sets m_curSpeed
  // Precondition: Must be populated
  // Postcondition: Sets m_curSpeed (does not calculate)
  virtual void SetCurSpeed(double);
  // Name: GetTopSpeed()
  // Description: Returns m_topSpeed
  // Precondition: Must be populated
  // Postcondition: Returns m_topSpeed (What is the top speed of the racer - provided)
  virtual double GetTopSpeed();
  // Name: GetHandling()
  // Description: Returns m_handling
  // Precondition: Must be populated
  // Postcondition: Returns m_handling (How well can the racer steer? - provided)
  virtual double GetHandling();
  // Name: GetAcceleration()
  // Description: Returns m_acceleration
  // Precondition: Must be populated
  // Postcondition: Returns m_acceleration (How fast can the racer accelerate?)
  virtual double GetAcceleration();
  // OPTIONAL: EXTRA CREDIT
  // DO NOT EDIT UNTIL YOU HAVE COMPLETED BASE PROJECT
  // Name: SpecialMove()
  // Description: Allows the child class to do a special move
  // Precondition: Must be implemented in the child class
  // Postcondition: Modifies something (think star, turbo, or something else interesting - MUST DO SOMETHING OTHER THAN JUST OUTPUT!)
  virtual void SpecialMove() = 0;
  // Name: CalcSpeed
  // Description: Calculates the current speed based on some rules described in project document
  // Precondition: Must be populated
  // Postcondition: Sets m_curSpeed
  virtual void CalcSpeed(double);
  // Name: Tick
  // Description: Checks to see if the racer crashes
  // Precondition: m_curSpeed must be calculated and passed maximum speed of track
  // Postcondition: May update m_curSpeed to 0 if there is a crash
  virtual void Tick(double);
private:
  double m_curLocation;//Current location
  double m_curSpeed;//Current Speed
  double m_topSpeed;//Top Speed (provided)
  double m_handling;//Handling (provided)
  double m_acceleration;//Acceleration (provided)
};
#endif
