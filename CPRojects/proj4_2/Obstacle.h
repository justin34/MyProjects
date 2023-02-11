//Title: Obstacle.h
//Author: Jeremy Dixon
//Date: 10/29/2021
//Description: Describes the parent class (Obstacles - bananas and shells)

#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <iostream>
#include <string>
using namespace std;

const int SPEED_LOST = 20;

//OPTIONAL CLASS FOR EXTRA CREDIT
//DO NOT EDIT UNTIL YOU HAVE COMPLETED THE BASE PROJECT

class Obstacle{
public:
  // Name: Obstacle (Default constructor)
  // Desc: Creates an Obstacle
  // Preconditions:  Abstract class
  // Postconditions: Abstract class so used with child classes only.
  Obstacle();

  // Name: Obstacle (Overloaded constructor)
  // Desc: Creates an Obstacle with 
  // Preconditions:  Abstract class
  // Postconditions: Abstract class so used with child classes only.
  Obstacle(string);
  
  // Name: ~Obstacle (Destructor
  // Desc: Deletes anything dynamically allocated
  // Preconditions:  Obstacle
  // Postconditions: Can be trivially implemented but required for subclass (tree)
  virtual ~Obstacle();
  
  //Accessors
  
  // Name: GetColor
  // Desc: Returns m_color
  // Preconditions:  None
  // Postconditions: None
  string GetColor();
  
  // Name: SetColor
  // Desc: Sets the color of an Obstacle
  // Preconditions:  None
  // Postconditions: m_color is set
  void SetColor(string color);
  
  // Name: Tick (Purely Virtual)
  // Desc: Calls Tick on the subtype (not implemented here)
  // Preconditions:  None
  // Postconditions: Implemented in child classes
  virtual void Tick(bool) = 0;

  // Name: GetType (Purely Virtual)
  // Desc: Returns the name of the subtype (not implemented here)
  // Preconditions:  None
  // Postconditions: Implemented in child classes
  virtual string GetType() = 0;

  // Name: Crash
  // Desc: A virtual function defined in the subtype
  // Precondition: An obstacle exists
  // Postcondition: A crash occurs
  virtual int Crash() = 0;
  
  // Name: overloaded operator<< (Purely Virtual)
  // Desc: Allows obstacles objects to be outputted
  // **NOTE** - Must be called with (*m_obstacles.at(i)) << cout << endl; (In this order)
  // Preconditions:  None
  // Postconditions: Implemented in child classes
  virtual ostream& operator<<(ostream& os) = 0;
 private:
  string m_color; //Current color
};

#endif
