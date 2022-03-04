#include "Track.h"
#include "Entity.h"
#include "Character.h"
#include "Mario.h"
#include "Obstacle.h"
#include "Shell.h"
#include "Banana.h"
#include "Game.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

int main () {
  srand(time(NULL)); //Do not use srand anywhere else
  
  //Some sample code to help test your code
  /*  const string fileName = "proj4_track1.txt";
  Track* newTrack = new Track();
  newTrack->LoadTrack(fileName);
  int index = newTrack->GetPiece(0);  
  newTrack->DisplayPiece(index);
  Entity* newChar = new Mario("Jeremy", 10, 10, 10);
  cout << "Distance = " << newChar->GetCurLocation() << endl;
  Obstacle* newShell = new Shell();
  newShell->Crash();
  Obstacle* newBanana = new Banana();
  */
  Game myGame;
  myGame.RaceSetup();
  myGame.LoadTrack();
  myGame.StartRace();
  return 0;
}
