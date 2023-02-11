#ifndef _MARIO_H
#define _MARIO_H

#include "Character.h"

//The hero of so many Nintendo games!
class Mario: public Character {
 public:
  // Name: Mario() - Default Constructor
  // Description: Creates a new Mario
  // Preconditions: None
  // Postconditions: Can create a Mario
  Mario();
  // Name: Mario(string name)
  // Description: Creates a new Mario
  // Preconditions: None
  // Postconditions: Can create a Mario
  Mario(string, double, double, double);
  // Name: ~Mario - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  ~Mario();
  // OPTIONAL: EXTRA CREDIT
  // Name: SpecialAttack
  // Description: Defines the Mario's special attack (up to you what it does)
  // Preconditions: None
  // Postconditions: Does something (think turbo, star etc. Must do something other than just changing output!)
  virtual void SpecialMove();
  // Name: GetType
  // Description: Returns the name of the object type (Mario in this case)
  // Precondition: Must be populated
  // Postcondition: Returns m_type (used to output)
  virtual string GetType();
  // Name: Overloaded << operator
  // Description: Returns information about the racer
  // Precondition: Must be populated
  // Postcondition: Returns something like Mario (J) has gone 348 meters and is currently going 80 m/s
  // Usage is *m_Racers.at(i) << cout << endl;
  virtual ostream& operator<<(ostream&);
};
#endif
