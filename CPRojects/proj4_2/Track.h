/*Title: Track.h
Author: Prof. Dixon
Date: 10/29/2021
Description: This class defines track and pieces of a track for a race in Mario Kart project
*/

#ifndef TRACK_H //Header Guard
#define TRACK_H //Header Guard
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//Simple structure used to describe each piece of the track. May be a straightaway, sharp curve, gentle curve etc.
struct Piece{
public:
  //Name: Piece (constructor)
  //Precondition: None
  //Postcondition: Holds data about the track pieces
  Piece(int length, string desc, int numBox, int max){
    m_length = length;
    m_desc = desc;
    m_numBox = numBox;
    m_maxSpeed = max;
  }
  string m_desc; //Description of the piece of the track
  int m_numBox; //Number of star boxes (earn obstacles?)
  int m_length; //Length of the piece of track
  int m_maxSpeed; //Max speed of that piece of track
};

class Track {
 public:
  // Name: Track
  // Precondition: None
  // Postcondition: Creates a new empty track
  Track();
  ~Track(); //Track Destructor
  // Name: LoadTrack(string fileName);
  // Description: Creates a piece of track from each line from input file
  // Precondition: m_filename is valid
  // Postcondition: Actually loads the track based on m_filename
  void LoadTrack(string fileName);
  // Name: GetPiece (int)
  // Description: At a specific distance, the corresponding index of the piece is returned
  // For example, if 300 is passed, iterates through vector adding distance until 300 is reached
  // If next piece of the track exceeds the end, returns the end
  // Precondition: Must have valid track and provided distance
  // Postcondition: Travels through track to described distance
  int GetPiece(int distance);
  // Name: DisplayPiece
  // Description: At a specific index, returns the m_desc from a particular piece of track
  // Precondition: Track loaded and a valid index passed
  // Postcondition: Returns id of track in that direction if the exit exists
  void DisplayPiece(int index);
  // Name: GetMaxSpeed
  // Description: At a specific index, returns the m_maxSpeed from a particular piece of track
  // Precondition: Track loaded and a valid index passed
  // Postcondition: Returns double which is max speed before racer crashes
  double GetMaxSpeed(int index);
  // Name: GetTotalLength()
  // Description: Returns m_totalLength
  // Precondition: Track loaded
  // Postcondition: Returns int for totallength
  int GetTotalLength();
  // Name: GetDesc()
  // Description: Returns m_desc
  // Precondition: Track loaded
  // Postcondition: Returns desc
  string GetDesc();
 private:
  string m_name; //Name of track
  string m_desc; //Description of track
  string m_fileName; //Filename of track to load
  vector<Piece*> m_track; //Vector holding track pieces
  int m_totalLength; //Total length of the track (calculated after loaded)
};
  #endif //Header Guard
