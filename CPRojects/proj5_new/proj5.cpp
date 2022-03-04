#include "Game.h"
#include "Hero.h"
#include "Lqueue.cpp"
#include "Villain.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

int main (int argc, char* argv[]) {
  srand(time(NULL)); //Do not use srand anywhere else
  if (argc < 2) {
      cout << "You are missing a data file." << endl;
      cout << "Expected usage ./proj5 proj5_data.txt" << endl;
      cout << "File 1 should be a file with a wizards" << endl;
      return 0;
    }
  Game myGame(argv[1]);
  myGame.LoadFile();
  myGame.MainMenu();
  return 0;
}
