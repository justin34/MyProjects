/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 0, Spring 2022
** Author:  Jabril Hall
** Date:    2/8/22
** Section: 2
** E-mail:  jhall14@umbc.edu
**
** File that tests the Elevator class implementation.
*/
#include "elevator.h"
class Tester{
    public:
        bool basicTestPassed(Elevator &elevator);
        bool removeTest(Elevator &elevator);
        bool insertTest(Elevator &elevator);
        bool EnterMoveExitTest(Elevator &elevator);
        bool copyConstructor(Elevator &elevator);
        bool assignmentOperator(Elevator &elevator);
        bool errorCases(Elevator &elevator);


    private:
        void fillList(Elevator &elevator, int BF, int TF){
            for (int i = BF; i <= TF; ++i) {
                elevator.insertAtTail(i);
            }
        }

        bool assignmentCheck(const Elevator &elevator, const Elevator &elevator1){
            Floor* current = elevator.m_top;
            Floor* current1 = elevator1.m_top;

            while (current != nullptr && current1 != nullptr){
                if (current == current1){
                    return false;
                }

                if(current->m_floorNum != current1->m_floorNum)
                    return false;

                if(current->m_passenger != current1->m_passenger)
                    return false;

                current1 = current1->m_next;
                current = current->m_next;
            }
            return true;

        }
};

int main(){

    Elevator testElevator;
    Tester tester;

    string result = tester.basicTestPassed(testElevator)? "True" : "False";
    cout << "Basic test passed?: " <<  result << endl;

    result = tester.removeTest(testElevator) ? "True" : "False";
    cout << "Remove test passed?: " <<  result << endl;

    result = tester.insertTest(testElevator) ? "True" : "False";
    cout << "Insert test passed?: " <<  result << endl;

    result = tester.EnterMoveExitTest(testElevator)? "True" : "False";
    cout << "Enter. Move. Exit passed?: " <<  result << endl;

    result = tester.copyConstructor(testElevator)? "True" : "False";
    cout << "Copy Constructor passed?: " <<  result << endl;

    result = tester.assignmentOperator(testElevator)? "True" : "False";
    cout << "Assignment operator passed?: " <<  result << endl;

    result = tester.errorCases(testElevator)? "True" : "False";
    cout << "error cases passed?: " <<  result << endl;


    return 0;
}

bool Tester::basicTestPassed(Elevator &elevator) {
    elevator.clear();
    for (int i = 0; i <= 150; ++i) {
        elevator.insertAtTail(i);
    }
    for (int i = -1; i >= -150; --i) {
        elevator.insertAtHead(i);
    }

    // elevator.dump();

    int floorCheck = -150;
    Floor* current = elevator.m_ground;

    while (current != nullptr){
        if(floorCheck != current->m_floorNum){
            return false;
        }
        floorCheck++;
        current = current->m_next;
    }



    return true;
}

bool Tester::removeTest(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, -150, 150);

    for (int i = -100; i <= 100; ++i) {
        elevator.removeFloor(i);
    }
    for (int i = 101; i <= 150; ++i) {
        elevator.removeFloor(i);
        elevator.removeFloor(i - (2*i));
    }
    if(elevator.m_ground != nullptr){
        return false;
    }

    return true;

}

bool Tester::insertTest(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, -100, 200);

    for (int i = -50; i < 150; i++) {
        elevator.removeFloor(i);
    }


    for (int i = 149; i >= -50; --i) {
        elevator.insertFloor(i);
    }

    // elevator.dump();

    int floorCheck = -100;
    Floor* current = elevator.m_ground;

    while (current != nullptr){
        if(floorCheck != current->m_floorNum){
            return false;
        }
        floorCheck++;
        current = current->m_next;
    }

    return true;

}

bool Tester::EnterMoveExitTest(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, -5, 5);

    elevator.enter(5,"Jabril");

    // elevator.dump();

    if(elevator.m_top->m_passenger != "Jabril"){
        return false;
    }

    elevator.move(5,1);

    // elevator.dump();

    Floor* current = elevator.m_top;

    while (current->m_floorNum != 1){
        current = current->m_previous;
    }
    if ((current->m_passenger != "Jabril") && (!elevator.m_top->m_passenger.empty())){
        return false;
    }

    if(elevator.exit(1,"Jabril") != "Jabril"){
        return false;
    }

    // elevator.dump();

    if (!current->m_passenger.empty())
        return false;

    return true;


}

bool Tester::copyConstructor(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, 5, 6);
    elevator.enter(6, "Jabril");

    Elevator copyElevator(elevator);

    return assignmentCheck(copyElevator, elevator);
}

bool Tester::assignmentOperator(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, 7, 7);
    elevator.enter(7, "Jabril");

    Elevator otherElevator;

    fillList(otherElevator, -4, 7);
    otherElevator.enter(3, "Najla");

    // otherElevator.dump();

    otherElevator = elevator;

    // otherElevator.dump();

    return assignmentCheck(otherElevator, elevator);

}

bool Tester::errorCases(Elevator &elevator) {
    elevator.clear();
    fillList(elevator, -50, 50);
    try { elevator.insertFloor(51); return false; } catch (out_of_range& e){ // out of range test
       // cout << "Out of range passed" << endl;
    }

    try { elevator.insertFloor(51); return false; } catch (out_of_range& e){ // out of range test
      //  cout << "Out of range passed" << endl;
    }

    if(elevator.insertAtHead(-60, "dad") || elevator.insertAtTail(60)){ return false;}
    // cout << "Insert head and tail out of order passed" << endl;

    try {elevator.insertFloor(50); return false;} catch (const char* e) { // duplicate floor test
       // cout << e << endl;
    }

    elevator.removeFloor(30);
    try{elevator.removeFloor(30); return false;} catch (const char* e) { // trying to remove a floor twice
      //  cout << e << endl;
    }

    elevator.clear();
    try{elevator.insertFloor(30); return false;} catch (const char* e) { // trying to insert to an empty list
       // cout << e << endl;
    }

    return true;

}
