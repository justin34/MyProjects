#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

class Hero{
 public:
  //Name: Hero (default constructor)
  //Precondition: None
  //Postcondition: Creates a Hero object
  Hero();
  //Name: Hero (Overloaded constructor)
  //Precondition: None
  //Postcondition: Creates a Hero object
  Hero(string name, string desc, int hp, int combat, int rarity);
  //Name: GetCombat()
  //Precondition: None
  //Postcondition: Returns the combat value of the Hero
  int GetCombat();
  //Name: GetHp()
  //Precondition: None
  //Postcondition: Returns the hit points of the Hero
  int GetHp();
  //Name: GetRarity()
  //Precondition: None
  //Postcondition: Returns the rarity of the Hero
  int GetRarity();
  //Name: GetName()
  //Precondition: None
  //Postcondition: Returns the name of the Hero
  string GetName();
  //Name: GetDesc()
  //Precondition: None
  //Postcondition: Returns the description of the Hero
  string GetDesc();

  //Name: SetHp()
  //Precondition: None
  //Postcondition: Sets the hp of the Hero
  void SetHp(int newHp);
  //Name: SetCP()
  //Precondition: None
  //Postcondition: Sets the combat value of the Hero
  void SetCombat(int newCombat);

  //Name: Train()
  //Precondition: Existing Hero
  //Postcondition: Increases the combat value of the Hero by 10
  void Train();
  //Name: Attack()
  //Precondition: Existing Hero
  //Postcondition: Displays attack details
  void Attack();
  //Name: operator<< (overloaded <<)
  //Precondition: Existing Hero
  //Postcondition: Prints information about the object
  friend ostream& operator<< (ostream& os, Hero &myHero);

 private:
  string m_name; //The Hero's name
  string m_desc; //The Hero's description
  int m_combat; //The Hero's combat value
  int m_hp; //The Hero's hit points
  int m_rarity; //The Hero's rarity (1-5)
};
#endif
