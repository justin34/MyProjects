/***********************************************************
 ** File:    Shell.h
 ** Project: UMBC Mario Kart
 ** Author:  Jeremy Dixon
 ** Date     11/1/2021
 ** Section: N/A
 ** This file contains the header file of the Shell class
 **********************************************************/
#ifndef SHELL_H
#define SHELL_H
#include "Obstacle.h"
#include <string>

//OPTIONAL CLASS FOR EXTRA CREDIT
//DO NOT EDIT UNTIL BASE PROJECT COMPLETED

class Shell: public Obstacle {
public:
  // Name: Shell (Default constructor)
  // Desc: Creates a shell
  // Preconditions:  Uses Obstacle default constructor
  // Postconditions: A shell is created.
  Shell();

  // Name: ~Shell
  // Desc: Destructor for shell
  // Preconditions:  Shell exists
  // Postconditions: Shell is cleared
  ~Shell();

  // Name: Tick
  // Desc: A turn triggers
  // Preconditions: Shell exists
  // Postconditions: Checks to see if a racer randomly runs into shell
  virtual void Tick(bool);

  // Name: Crash
  // Desc: Decreases speed of racer and makes them spin out
  // Preconditions:  Shell exists
  // Postconditions: Speed returned is amount of speed reduced
  virtual int Crash();

  // Name: GetType
  // Desc: Returns the name of the subtype (Shell)
  // Preconditions:  None
  // Postconditions: Returns string name of the subtype (Shell)
  virtual string GetType();
  
  // Name: overloaded operator<<
  // Desc: Allows Shell objects to be outputted
  // Preconditions:  None
  // Postconditions: Outputs shell description
  virtual ostream& operator<<(ostream&);

};

#endif 
