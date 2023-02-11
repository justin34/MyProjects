#ifndef _TOAD_H
#define _TOAD_H

#include "Character.h"


class Toad: public Character {
 public:
  // Name: Toad() - Default Constructor
  // Description: Creates a new Toad
  // Preconditions: None
  // Postconditions: Can create a Toad
  Toad();
  // Name: Toad(string name)
  // Description: Creates a new Toad
  // Preconditions: None
  // Postconditions: Can create a Toad
  Toad(string, double, double, double);
  // Name: ~Toad - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  ~Toad();
  // OPTIONAL: EXTRA CREDIT
  // Name: SpecialAttack
  // Description: Defines the Toad's special attack (up to you what it does)
  // Preconditions: None
  // Postconditions: Does something (think turbo, star etc. Must do something other than just changing output!)
  virtual void SpecialMove();
  // Name: GetType
  // Description: Returns the name of the object type (Toad in this case)
  // Precondition: Must be populated
  // Postcondition: Returns m_type (used to output)
  virtual string GetType();
  // Name: Overloaded << operator
  // Description: Returns information about the racer
  // Precondition: Must be populated
  // Postcondition: Returns something like Toad (J) has gone 348 meters and is currently going 80 m/s
  // Usage is *m_Racers.at(i) << cout << endl;
  virtual ostream& operator<<(ostream&);
};
#endif
