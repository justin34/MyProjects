#ifndef GAME_H
#define GAME_H

#include "Hero.h"
#include "Villain.h"
#include "Lqueue.cpp"
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

//Constants
const int RARITY [5] = {65,45,25,10,5}; //Likelihood of aquiring a rare hero
const string SEP =  "***************************************"; //Used for formatting
const int MAX_HEROES = 5; //Maximum number of heroes on team (otherwise too busy!)
const int MAX_VILLAINS = 5; //Maximum number of villains on team (too busy)

class Game{
 public:
  Game(string f_fileName); //Constructor for Game
  ~Game(); //Destructor for Game
  // Name: LoadFile
  // Precondition: m_fileName must be populated
  // Postcondition: populates both m_heroes and m_villians from a file
  // Should be: Heros loaded: 230 Villains Loaded: 94 Total Loaded: 324
  void LoadFile();
  // Name: PrintHeroes
  // Precondition: m_heroes must be populated
  // Postcondition: prints all heroes in m_heroes
  void PrintHeroes();
  // Name: PrintVillains
  // Precondition: m_villains must be populated
  // Postcondition: prints all villians in m_villians
  void PrintVillains();
  // Name: PrintMyHeroes();
  // Precondition: m_myHeroes must be populated
  // Postcondition: prints all heroes found in m_myHeroes
  void PrintMyHeroes();
  // Name: AcquireHero
  // Pre-condition: Requires m_heroes vector to be populated
  // Post-condition: Prompts user for rarity (1-5) user would like to capture
  //          Based on rarity (1=65%, 2=45%, 3=25%, 4=10%, 5=1%) tries to find a random
  //          Hero based on that rarity.
  //          If a Hero is found, calls FoundHero else indicates no hero was found
  void AcquireHero();
  // Name: FoundHero ()
  // Pre-condition: If a Hero is found in AcquireHero, rarity is passed to this function
  // Post-condition: Using rarity, a m_heroes is randomly searched for
  //                 a matching rarity also uses Lqueue.Find to make
  //                 sure that new wizard is unique (can only have one of each)
  //                 After an appropriate Hero is found
  //                 Adds new Hero to user's m_myHeroes
  void FoundHero(int rarity);
  // Name: MainMenu
  // Pre-condition: None
  // Post-condition: Calls a variety of functions based on user
  void MainMenu();
  // Name: PrepareVillains
  // Pre-condition: Asks the user how many villians to battle (up to MAX_VILLAINS)
  //                Has the computer randomly add villians to send to battle to m_bVillains Tqueue
  // Post-condition: Battle continues
  void PrepareVillains();
  // Name: PrepareHeroes
  // Pre-condition: Populates m_bHeroes from myHeroes
  //                Can add up to MAX_HEROES heroes per battle
  //                Could add the SAME hero more than once to the battle queue (not checked)
  // Post-condition: Battle continues
  void PrepareHeroes();
  // Name: Battle
  // Pre-condition: Calls PrepareVillains to populate m_bVillains
  //                Calls PrepareHeroes it populate m_bHeroes
  //                Hero attacks first then if villian still alive villian attacks
  //                If hp is below 0 then hero or villian is dequeued from their battle queue
  // Post-condition: Calls ResolveBattle to identify winner
  void Battle();
  // Name: ResolveBattle
  // Pre-condition: If m_bHeroes has heroes left, they win else villians win
  // Post-condition: None
  void ResolveBattle();
  // Name: TrainHero()
  // Pre-condition: User chooses hero from myHero to train
  // Post-condition: Calls Train member function that increases Combat by 10.
  //                 Updates hero's combat in m_myHeroes
  void TrainHero();
 private:
  vector<Hero*> m_heroes; //Vector of all possible Heroes
  vector<Villain*> m_villains; //Vector of all possible Villains
  Lqueue<Hero*> m_myHeroes; //Queue of all heroes found and trained
  Lqueue<Hero*> m_bHeroes; //Queue of heroes to battle (populated in PrepareHeroes)
  Lqueue<Villain*> m_bVillains; //Queue of villians to battle (populated in PrepareVillains)
  string m_fileName; //File name for all heroes and villians to be loaded
};
#endif
