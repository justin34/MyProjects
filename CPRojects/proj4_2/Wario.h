#ifndef _WARIO_H
#define _WARIO_H

#include "Character.h"


class Wario: public Character {
 public:
  // Name: Wario() - Default Constructor
  // Description: Creates a new Wario
  // Preconditions: None
  // Postconditions: Can create a Wario
  Wario();
  // Name: Wario(string name)
  // Description: Creates a new Wario
  // Preconditions: None
  // Postconditions: Can create a Wario
  Wario(string, double, double, double);
  // Name: ~Wario - Virtual Destructor
  // Description: Makes sure everything in child class is deallocated
  // Preconditions: None
  // Postconditions: Everything dynamically allocated is deallocated
  ~Wario();
  // OPTIONAL: EXTRA CREDIT
  // Name: SpecialAttack
  // Description: Defines the Wario's special attack (up to you what it does)
  // Preconditions: None
  // Postconditions: Does something (think turbo, star etc. Must do something other than just changing output!)
  virtual void SpecialMove();
  // Name: GetType
  // Description: Returns the name of the object type (Wario in this case)
  // Precondition: Must be populated
  // Postcondition: Returns m_type (used to output)
  virtual string GetType();
  // Name: Overloaded << operator
  // Description: Returns information about the racer
  // Precondition: Must be populated
  // Postcondition: Returns something like Wario (J) has gone 348 meters and is currently going 80 m/s
  // Usage is *m_Racers.at(i) << cout << endl;
  virtual ostream& operator<<(ostream&);
};
#endif
