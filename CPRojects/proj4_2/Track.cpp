/*****************************************
** File:    Track.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/10/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Track.h.
*/

#include "Track.h"

Track::Track() { // provides standard definitions
    m_name = "";
    m_fileName = "";
    m_desc = "give me file";
    m_totalLength = 0;
}

Track::~Track() {
    for (Piece *& piece: m_track){ // deletes pieces in m_track
        delete piece;
    }
}

void Track::LoadTrack(string fileName) {
    fstream newfile;
    m_fileName = fileName;
    newfile.open(m_fileName, ios::in);
    cout << "atempting" << endl;
    if (newfile.is_open()) {   //checking whether the file is open
        cout << "file is open" << endl;
        string name, desc, pieceName, strlength, strBoxNum, strMaxSpeed;
        int lengh, numBox, maxSpeed;

        // first two line of the file will be name followed by description.
        getline(newfile, name, '\n');
        getline(newfile,desc, '\n');

        m_name = name;
        m_desc = desc;
        while (getline(newfile, strlength, '|')){
            string blank;
            //gets information from file
            getline(newfile, pieceName, '|');
            getline(newfile, strBoxNum, '|');
            getline(newfile, strMaxSpeed, '|');
            getline(newfile, blank, '\n');

            // converts the strings to ints
            lengh = stoi(strlength);
            numBox = stoi(strBoxNum);
            maxSpeed = stoi(strMaxSpeed);

            Piece* newPiece = new Piece(lengh, pieceName, numBox, maxSpeed); // makes a new piece with the info

            m_track.push_back(newPiece); // adds it to track
        }

        cout << "Track loaded: \n\t Name: " << m_name << "\n\t Number of pieces: " << m_track.size() << endl;
    }
    newfile.close();

    m_totalLength = 0;
    for(Piece *& piece : m_track){
        m_totalLength += piece->m_length;
    }
}

void Track::DisplayPiece(int index) {
    if(index < m_track.size())
        cout << m_track[index]->m_desc << endl;
    else
        cout << "Finish" << endl;
}

double Track::GetMaxSpeed(int index) {
    return m_track[index]->m_maxSpeed;
}

string Track::GetDesc() {
    return m_desc;
}

int Track::GetTotalLength() {

    return m_totalLength;
}

int Track::GetPiece(int distance) {
    int lastLength = 0;
    int nextLength = 0;
    int lastPiece = m_track.size() - 1;

    if (distance >= m_totalLength)
        return lastPiece;

    for(int i = 0; i < m_track.size(); i++){
        lastLength = nextLength;
        nextLength += m_track[i]->m_length;

        if (distance >= lastLength && distance < nextLength){
            return i;
        }
    }

    return -1;

}

