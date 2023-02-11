#ifndef VILLAIN_H
#define VILLAIN_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class Villain{
 public:
  //Name: Villain (default constructor)
  //Precondition: None
  //Postcondition: Creates a Villain wizard object
  Villain();
  //Name: Villain (Overloaded constructor)
  //Precondition: None
  //Postcondition: Creates a Villian wizard object
  Villain(string name, string desc, int hp, int combat, int rarity);
  //Name: GetCombat()
  //Precondition: None
  //Postcondition: Returns the combat value of the Villain wizard
  int GetCombat();
  //Name: GetHp()
  //Precondition: None
  //Postcondition: Returns the hit points of the Villain wizard
  int GetHp();
  //Name: GetRarity()
  //Precondition: None
  //Postcondition: Returns the rarity of the Villain wizard
  int GetRarity();
  //Name: GetName()
  //Precondition: None
  //Postcondition: Returns the name of the Villain wizard
  string GetName();
  //Name: GetDesc()
  //Precondition: None
  //Postcondition: Returns the description of the Villain wizard
  string GetDesc();

  //Name: SetHp()
  //Precondition: None
  //Postcondition: Sets the hp of the Villain
  void SetHp(int newHp);
  //Name: SetCombat()
  //Precondition: None
  //Postcondition: Sets the combat value of the Villain
  void SetCombat(int newCombat);
  //Name: Attack()
  //Precondition: Existing Villain
  //Postcondition: Displays attack details
  void Attack();
  //Name: operator<< (overloaded <<)
  //Precondition: Existing Villain
  //Postcondition: Prints information about the object
  friend ostream& operator<< (ostream& os, Villain &myVillain);

 private:
  string m_name; //The Villain's name
  string m_desc; //The Villain's description
  int m_combat; //The Villain's combat value
  int m_hp; //The Villain's hit points
  int m_rarity; //The Villain's rarity (1-5)
};
#endif
