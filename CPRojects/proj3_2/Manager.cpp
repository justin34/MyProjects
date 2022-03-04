/*****************************************
** File:    Manager.cpp
** Project: CMSC 202 Project 3, Fall 2021
** Author:  Jabril Hall
** Date:    10/25/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Manager.h.
*/

#include "Manager.h"

Manager::Manager(string fileName) {
    m_fileName = fileName;
    ReadFile();
    MainMenu();
}

Manager::~Manager() {
    for (Schedule *& m_schedule : m_schedules){
        delete m_schedule;
    }
}

void Manager::ReadFile() {
    fstream newfile;
    newfile.open(m_fileName, ios::in);
    cout << "atempting" << endl;
    if (newfile.is_open()){   //checking whether the file is open
        cout << "file is open" << endl;
        string scheduleName, itemName, strTime; // variables for item and schedule
        int numTime;
        int nodeCount;
        while(getline(newfile, scheduleName, ';')){ // while it still finds a name
            // collect information from file
            getline(newfile, strTime, ';');
            getline(newfile, itemName, '\n');
            numTime = stoi(strTime);
            // try to add item to an existing schedule
            bool added = false;
            for (Schedule* & m_schedule : m_schedules){
                if(scheduleName == m_schedule->GetName() && !added){ // checks if the name is already in the vector
                    Item* item = new Item(itemName, numTime);
                    m_schedule->InsertSorted(item);
                    added = true;
                    nodeCount++;
                }
            }
            // if not added make a new schedule
            if(!added){
                Item* item = new Item(itemName, numTime);
                Schedule* schedule = new Schedule(scheduleName);
                schedule->InsertSorted(item);

                m_schedules.push_back(schedule);
                nodeCount++;
            }
        }

        cout << nodeCount << " Node(s) and "<< m_schedules.size() << " Schedule(s) loaded" << endl;
        newfile.close(); //close the file object.
    }
}

void Manager::ReverseSchedule() {
    if (m_schedules.size() == 1){
        m_schedules[0]->ReverseSchedule();
        cout << m_schedules[0]->GetName() << " was reversed" << endl;
        return;
    }

    DisplaySchedules();
    cout << "Who's schedule do you want to reverse: " << endl;
    string scheduleName;
    cin >> scheduleName;

    int indexOfSched = FindSchedule(scheduleName);

    if(indexOfSched == -1){
        cout << "Could not find schedule";

    }else{
        m_schedules[indexOfSched]->ReverseSchedule();
        cout << m_schedules[indexOfSched]->GetName() << " was reversed" << endl;
    }
}

void Manager::DisplaySchedules() {
    for (Schedule *& schedule : m_schedules){
        cout << *schedule << endl;
    }
}

int Manager::FindSchedule(string schedName) {
    int index = 0;
    for (Schedule *& schedule : m_schedules){
        if (schedule->GetName() == schedName){
            return index;
        }
        index++;
    }

    return -1;
}

void Manager::InsertNewItem() {
    DisplaySchedules();
    cout << "Who's schedule do you want to add to: " << endl;
    string scheduleName;
    cin >> scheduleName;

    int indexOfSched = FindSchedule(scheduleName);

    if(indexOfSched == -1)
        cout << "Couldn't find schedule" << endl;
    else{
        int time;
        string name;
        cout << "Enter Time: " << endl;
        cin >> time;
        cout << "Enter Name:" << endl;
        cin >> name;

        Item* item = new Item(name, time);
        m_schedules[indexOfSched]->InsertSorted(item);
    }
}

void Manager::MainMenu() {
    int choice;

    cout << "What would you like to do?:\n"
            "1. Display Schedules\n"
            "2. Reverse Schedules\n"
            "3. Insert New Item\n"
            "4. Exit" << endl;
    cin >> choice;

    while (choice > 4 || choice < 0){
        cin.clear();
        cin >> choice;
    }



    while (choice != 4){
        switch (choice) {
            case 1:
                DisplaySchedules();
                break;
            case 2:
                ReverseSchedule();
                break;
            case 3:
                InsertNewItem();
                break;
            default:
                cout << "ERROR" << endl;

        }
        cout << "What would you like to do?:\n"
                "1. Display Schedules\n"
                "2. Reverse Schedules\n"
                "3. Insert New Item\n"
                "4. Exit" << endl;
        cin >> choice;

        while (choice > 4 || choice < 0){
            cin.clear();
            cin >> choice;
        }
    }
}