/*****************************************
** File:    Game.cpp
** Project: CMSC 202 Project 4, Fall 2021
** Author:  Jabril Hall
** Date:    11/15/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Game.h.
*/

#include "Game.h"

Game::Game() {

}

Game::~Game() {
    for(Entity * racer: m_Racers){ // deletes each racer in the vector
        delete racer;
    }
}

void Game::LoadTrack() { // loads track
    // asks user for number of laps and which track.
    int trackNum;
    cout << "How many laps would you like to complete for the race?" << endl;
    cin >> m_numLaps;
    while (m_numLaps < 1){
        cout << "How many laps would you like to complete for the race?" << endl;
        cin >> m_numLaps;
    }

    cout << "Which track would you like to use?" << endl;
    for (int i = 0; i < NUM_TRACKS; i++){
        cout << i+1 << ". " << TRACK[i][0] << endl;
    }
    cin >> trackNum;

    while (trackNum > 3 || trackNum < 1){
        cout << "Which track would you like to use?\n";
        cin >> trackNum;
    }
    // loads the track the user chose for each lap
    for (int i = 0; i < m_numLaps; i++){
        myTrack.LoadTrack(TRACK[trackNum-1][1]);
    }


}

void Game::RaceSetup() {
    // sets up users racer
    cout << "What is your name?" << endl;
    string userName;
    cin >> userName;

    int racerNum;
    cout << "Select a Racer\n"
            "1. Toad\n"
            "2. Wario\n"
            "3. Mario" << endl;
    cin >> racerNum;

    while (racerNum > 3 || racerNum < 1){
        cout << "Which racer would you like to use?\n";
        cin >> racerNum;
    }

    // creates a character based on what the user chose
    if(racerNum == 1){
        Toad *player = new Toad(userName, TOAD_STATS[0], TOAD_STATS[1], TOAD_STATS[2]);
        m_Racers.push_back(player);
    } else if(racerNum == 2){
        Wario *player = new Wario(userName, WARIO_STATS[0], WARIO_STATS[1], WARIO_STATS[2]);
        m_Racers.push_back(player);
    } else if(racerNum == 3){
        Mario *player = new Mario(userName, MARIO_STATS[0], MARIO_STATS[1], MARIO_STATS[2]);
        m_Racers.push_back(player);
    }

    m_playerName = userName;

    // sets up cpus
    int numRacers;
    cout << "How many racers do you want?" << endl;
    cin >> numRacers;

    for (int i = 0; i < numRacers; i++){
        string cpuName = "CPU" + to_string(i); // creates a name for each cpu
        racerNum = (rand() % 3) + 1;

        // selects a random character for that cpu
        if(racerNum == 1){
            Toad* player = new Toad(cpuName, TOAD_STATS[0], TOAD_STATS[1], TOAD_STATS[2]);
            m_Racers.push_back(player);
        } else if(racerNum == 2){
            Wario* player = new Wario(cpuName, WARIO_STATS[0], WARIO_STATS[1], WARIO_STATS[2]);
            m_Racers.push_back(player);
        } else if(racerNum == 3){
            Mario* player = new Mario(cpuName, MARIO_STATS[0], MARIO_STATS[1], MARIO_STATS[2]);
            m_Racers.push_back(player);
        }
    }

    m_numRacers = m_Racers.size();

}

void Game::StartRace() {
    // prints beginning output
    cout << "You will be racing " << m_numLaps << "lap(s)" << endl;
    cout << "The total length of the race is " << myTrack.GetTotalLength() << " meters" << endl;
    myTrack.DisplayPiece(0);
    cout << "*********ON YOUR MARKS*********\n"
            "\n"
            "*********GET SET*********\n"
            "\n"
            "*********GO! GO! GO!*********" << endl;
    bool raceBegan = false;
    int choice = 0;
    int round = 0;
    while(!CheckFinish() && choice != 6){
        if(!raceBegan){ // different output for the beginning of the race
            cout << "You\'re at the start of the race." << endl;
            cout << "Ahead is:" << endl;
            myTrack.DisplayPiece(myTrack.GetPiece(m_Racers.at(FindPlayer())->GetCurLocation())+1);
            raceBegan = true;
        } else { // output after beginning
            Display();
            cout << "****************************\n"
                    "Round: " << round << "\n"
                    "****************************\n"
                    "You currently see:" <<endl;
            myTrack.DisplayPiece(myTrack.GetPiece(m_Racers.at(FindPlayer())->GetCurLocation()));
            cout << "Ahead is:" << endl;

            myTrack.DisplayPiece(myTrack.GetPiece(m_Racers.at(FindPlayer())->GetCurLocation())+1);
        }
        // gets a choice from the player
        choice = Action();
        switch (choice) { // sets the speed based on choice
            case 1:
                m_Racers.at(FindPlayer())->CalcSpeed(1.0);
                break;
            case 2:
                m_Racers.at(FindPlayer())->CalcSpeed(0.75);
                break;
            case 3:
                m_Racers.at(FindPlayer())->CalcSpeed(0.5);
                break;
            case 4:
                m_Racers.at(FindPlayer())->CalcSpeed(0.25);
                break;
            case 5:
                Attack();
        }
        CpuRandom(); // randomizes cpu speed
        Tick(0.0); // ticks each racer
        Order(); // reorders the list after tick
        round++; // increments round
    }
}

int Game::Action() { // gets a action from the player
    int choice;
    cout << "What do you whant to do?\n"
            "1. Max Speed\n"
            "2. Pretty Fast\n"
            "3. Fast\n"
            "4. Slow\n"
            "5. Use Obstacle\n"
            "6. Quit" << endl;
    cin >> choice;
    return choice;
}

void Game::Tick(double uslessNumber) {
    for (int i = 0; i < m_numRacers; ++i) { // gets max speed for the track the racer's on for each racer
        int pieceIndex = myTrack.GetPiece(m_Racers[i]->GetCurLocation()); // gets the piece
        int maxSpeed = myTrack.GetMaxSpeed(pieceIndex); // gets max speed
        m_Racers[i]->Tick(maxSpeed); // calls tick with max speed
    }
}

int Game::FindPlayer() { // finds the index player in m_Racers
    for (int i = 0; i < m_numRacers; ++i) {
        if (m_Racers[i]->GetName() == m_playerName){
            return i;
        }
    }

    return -1;
}

bool Game::CheckFinish() {
    for(int i = 0; i < m_numRacers; ++i){ // Checks if any racers has a location longer than the track
        double currentLocation = m_Racers[i]->GetCurLocation();
        if(currentLocation >= myTrack.GetTotalLength()){
            cout << m_Racers[i]->GetName() << " has compleated the race.";
            return true;
        }
    }
    return false;
}

void Game::CpuRandom() {
    for (int i = 0; i < m_numRacers; ++i) {
        if(i != FindPlayer()){
            double randomNum = (rand() % 4) + 1;
            m_Racers[i]->CalcSpeed(randomNum / 4.0); // sets a random speed for the CPU's
        }
    }
}

void Game::Order() {
    bool switched = true;
    // bubble sort to order m_Racers
    while (switched){
        switched = false;
        for (int i = 0; i < m_numRacers - 1; ++i) {
            if(m_Racers[i]->GetCurLocation() < m_Racers.at(i+1)->GetCurLocation()){
                Entity* temp = m_Racers[i];
                m_Racers[i] = m_Racers.at(i+1);
                m_Racers.at(i+1) = temp;
                switched = true;
            }
        }
    }
}

void Game::Display() {
    // prints each racer
    cout << "******************************" << endl;
    for (int i = 0; i < m_numRacers; ++i) {
        *m_Racers[i] << cout << endl;
    }

    cout << "******************************" << endl;
}

void Game::Attack() { // doesnt do much
    m_Racers.at(FindPlayer())->SpecialMove();
}