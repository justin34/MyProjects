/***********************************************************
 ** File:    Game.h
 ** Project: UMBC Mario Kart
 ** Author:  Jeremy Dixon
 ** Date     11/1/2021
 ** Section: N/A
 ** This file contains the header file of the Game class
 **********************************************************/
#ifndef _GAME_H_
#define _GAME_H_

//Includes of required classes
#include "Track.h"
#include "Entity.h"
#include "Mario.h"
#include "Wario.h"
#include "Toad.h"
#include "Obstacle.h"
#include "Banana.h"
#include "Shell.h"

//Includes of required libraries
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

//************************Constants*********************
//STATS are top speed, acceleration, and handling
const double TOAD_STATS[] = {40, 6.5, 9.5};
const double WARIO_STATS[] = {90, 5, 6};
const double MARIO_STATS[] = {80, 6, 6};
//TRACK FILES
const int NUM_TRACKS = 3;
const string TRACK[NUM_TRACKS][2] = {{"Mario's Drag Race","proj4_track1.txt"},
			    {"Mario Circuit 1", "proj4_track2.txt"},
			    {"Ultra Race","proj4_track3.txt"}};
//******************************************************

class Game {
public:
  // Name: Game() - Default Constructor
  // Description: Creates a new Game. Welcomes player to UMBC Mario Kart. Initializes laps and racers to 1
  // Preconditions: None
  // Postconditions: m_numLaps and m_numRacers initialized to 1
  Game();
  // Name: ~Game
  // Description: Destructor
  // Preconditions: None
  // Postconditions: Deallocates anything dynamically allocated in Game
  ~Game();
  // Name: LoadTrack
  // Description: Asks user which track to use (1-3)
  //              Calls LoadTrack for use in myTrack
  //              If three laps then the same track is loaded three times
  // Precondition: Files must exist. m_numLaps must be populated
  // Postcondition: myTrack is populated with track Pieces
  void LoadTrack();
  // Name: RaceSetup
  // Description: Asks the user for their name and stores it in local variable
  //              Allows user to choose which racer to use (Mario, Wario, or Toad) using provided name
  //              Allows the user to choose how many other racers to use (no limit) - Randomly assigned (can be duplicates)
  //              Allows the user to choose how many laps to race (no limit)
  // Preconditions: None
  // Postconditions: m_Racers populated with racers, m_numLaps populated
  void RaceSetup();
  // Name: StartRace()
  // Description: As long as the race isn't over or the user hasn't quit repeat these:
  //              Displays current position in track for user
  //              Shows round number
  //              Displays current piece description on track
  //              Displays the next piece description on track (like what is ahead)
  //              Makes computer racers randomly choose a speed for this round (100%, 75%, 50%, 25%)
  //              Tick (passing max speed)
  //              Reorder vector based on who has moved the most down the track (m_curLocation)
  //              Display the order
  // Preconditions: LoadTrack and RaceSetup must have been completed
  // Postconditions: Continues until race is over. If completed, displays result (who won)
  void StartRace();
  // Name: CheckFinish
  // Description: Checks to see if any racer has exceeded total length of the track
  // Precondition: m_Racers has been populated and myTrack has been populated
  // Postcondition: Returns true if race is over; else false
  bool CheckFinish();
  // Name: CpuRandom
  // Description: Iterates over all computer m_Racers and uses CalcSpeed to randomly assign either (100%, 75%, 50%, 25%)
  // Precondition: m_Racers has been populated
  // Postcondition: Using CalcSpeed, updates racer's speeds
  void CpuRandom();
  // Name: Tick
  // Description: Iterates over all computer m_Racers and calls Tick and passes the maxSpeed of the current piece of track that racer is on
  // Precondition: m_Racers has been populated and myTrack has been populated
  // Postcondition: Checks to see if the racer crashes by exceeding the max limit of that track piece
  void Tick(double);
  // Name: Order
  // Description: Uses a simple bubble sort (nested for loops) to reorder who has traveled the farthest
  // Precondition: m_Racers has been populated
  // Postcondition: m_Racers is sorted from highest distance traveled to lowest distance traveled
  void Order();
  // Name: Attack
  // Description: Optional-extra credit
  //              Uses obstacles to make things crash. Uses bananas to make racers crash behind the user
  //              Uses shells to crash racers ahead.
  //              Can only attempt after the base project is completed
  //              Can add additional member functions and variables to make this functionality work
  void Attack();
  // Name: Display
  // Description: Displays each racer in m_Racers by using overloaded << operator
  // Precondition: m_Racers has been populated
  // Postcondition: Usage is *m_Racers.at(i) << cout << endl;
  void Display();
  // Name: Tick
  // Description: Iterates over all racers in m_Racers to return the index of where the player's racer exists (after sort)
  // Precondition: m_Racers has been populated and sort has been called
  // Postcondition: Returns the index of where the player's racer exists
  int FindPlayer();
  // Name: Action()
  // Description: Menu for game
  //              Required to implement cases 1-4 and 6.
  //              Choice 5 (Attack) is optional and is part of the extra credit
  //              Asks the user if they want to change their speed
  // Preconditions: Everything in start has been completed
  // Postconditions: Game continues until someone finishes race
  int Action();
private:
  Track myTrack; //Creates a track for the racers
  vector<Entity*> m_Racers; // Vector for all people in the race (Toad, Mario, or Wario)
  int m_numLaps; //Number of laps in race
  int m_numRacers; //Number of racers in race
  string m_playerName; //Name of the player 
};

#endif
