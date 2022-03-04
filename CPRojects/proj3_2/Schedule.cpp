/*****************************************
** File:    Schedule.cpp
** Project: CMSC 202 Project 3, Fall 2021
** Author:  Jabril Hall
** Date:    10/24/21
** Section: 31
** E-mail:  jhall14@umbc.edu
**
** This file contains the implementation for Schedule.h.
*/

#include "Schedule.h"

Schedule::Schedule() {
    m_name = "UNDEFINED";
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Schedule::Schedule(string name) {
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

Schedule::~Schedule() {

    // sets up a current and next
    Item *current = m_head;
    Item *next = nullptr;

    while (current != nullptr){

        // delete the current "current" and then sets it equal to next
        next = current->GetNext();
        delete current;
        current = next;
    }

    m_head = nullptr;

}

Item *Schedule::GetData(int nodeNum) {

    // guard if statement to protect against non-valid nodNums
    if (nodeNum > m_size || nodeNum <= 0)
        return nullptr;

    int counter = 1;
    Item *current = m_head;

    while (counter != nodeNum){
        current = current->GetNext();
        counter++;
    }

    return current;
}

void Schedule::InsertSorted(Item *item) {

    // if it is an empty list set the head to item
    if (m_size == 0) {
        m_head = item;
        m_tail = m_head;
        m_size++;
        return;
    }

    //sorts the item into the schedule
    int minListTime = m_head->GetTime();
    int maxListTime = m_tail->GetTime();


    // sets it to the tail or the head if its greater or less than the mins and max
    if(item->GetTime() < minListTime){
        item->SetNext(m_head);
        m_head = item;
        m_size++;
        return;
    }
    if (item->GetTime() > maxListTime){
        m_tail->SetNext(item);
        m_tail = item;
        m_size++;
        return;
    }



    // adds it to the middle the right location
    Item *current = m_head;
    Item *next;

    while(current->GetNext() != nullptr){
        next = current->GetNext();

        // since the list is in order if the new time is less than on it goes before it
        if(item->GetTime() < next->GetTime()){
            item->SetNext(next);
            current->SetNext(item);
            m_size++;
            return;
        }
        current = current->GetNext();
    }

    // increment size
}

void Schedule::ReverseSchedule() {
    Item *current = m_head;
    Item *previous = nullptr;
    Item *next = nullptr;

    while (current != nullptr){
        // save place of next value
        next = current->GetNext();

        // set the next value of current to the previous value
        current->SetNext(previous);

        // set the new previous to current
        previous = current;
        // set current to the original next
        current = next;

    }

    // set head to the last value of current
    m_head = previous;
}

string Schedule::GetName() {
    return m_name;
}

int Schedule::GetSize() {
    return m_size;
}



ostream &operator<< (ostream &output, Schedule &mySchedule){
    output << "Schedule for " << mySchedule.m_name << endl;
    output << mySchedule.m_size << " activities scheduled\n";

    Item *current = mySchedule.m_head;

    while (current != nullptr){
        output << *current << endl;
        current = current->GetNext();
    }

    return output;
}