// UMBC - CMSC 341 - Spring 2022 - Proj1
#include "elevator.h"
Elevator::Elevator(){
    // set pointers to null
    m_ground = nullptr;
    m_top = nullptr;
}
Elevator::~Elevator(){
    // create temp values
    Floor* current = m_ground;
    Floor* previous;

    // iterate threw the list deleting every pointer behind it
    while(current != nullptr){
        previous = current;
        current = current->m_next;
        delete previous;
    }
    m_ground = nullptr;
    m_top = nullptr;

}
void Elevator::clear(){
    // same as deconstructor
    Floor* current = m_ground;
    Floor* previous;

    while(current != nullptr){
        previous = current;
        current = current->m_next;
        delete previous;
    }
    m_ground = nullptr;
    m_top = nullptr;
}
bool Elevator::insertAtHead(int floor, string passenger){

    // if head is null assign it the first value
    if (m_ground == nullptr){
        m_ground = new Floor(floor, passenger);
        m_top = m_ground; // point tail to the same place
        return true;
    }

    // if the floor being added is not one less than the current ground return false
    if (floor != m_ground->m_floorNum-1)
        return false;

    // create a new floor and intergrate it into the list
    Floor* newFloor = new Floor(floor, passenger);

    newFloor->m_next = m_ground;
    m_ground->m_previous = newFloor;
    m_ground = newFloor;

    return true;


}
// same as insert head but ever next is replaced with previous and vice versa
bool Elevator::insertAtTail(int floor, string passenger){
    if (m_top == nullptr){
        m_top = new Floor(floor, passenger);
        m_ground = m_top;
        return true;
    }

    if (floor != m_top->m_floorNum+1)
        return false;

    Floor* newFloor = new Floor(floor, passenger);

    newFloor->m_previous = m_top;
    m_top->m_next = newFloor;
    m_top = newFloor;

    return true;
}

bool Elevator::removeFloor(int floor){
    // if the floor is out of the range of the list throw an error
    if(m_ground->m_floorNum > floor || m_top->m_floorNum < floor)
        throw out_of_range("INDEX OUT OF RANGE");

    if(!checkFloor(floor)){
        throw "FLOOR DOESNT EXIST";
    }
    // if the list is empty throw an error
    if(m_ground == nullptr)
        throw "EMPTY ELEVATOR LIST";


    if(m_ground == m_top){
        clear();
        return true;
    }

    if(m_ground->m_floorNum == floor){
        Floor* del = m_ground;
        m_ground = m_ground->m_next;
        if (m_ground != nullptr)
            m_ground->m_previous = nullptr;
        delete del;
        return true;
    }
    if(m_top->m_floorNum == floor){
        Floor* del = m_top;
        m_top = m_top->m_previous;
        if (m_top != nullptr)
            m_top->m_next = nullptr;
        delete del;
        return true;
    }

    // find the middle number
    int middle = abs(m_ground->m_floorNum - m_top->m_floorNum)/2;
    bool startFromEnd = true;
    if(floor <= (m_ground->m_floorNum + middle)) // if the floor is closest to m_ground set startFromEnd to false
        startFromEnd = false;

    // if the fastest way to the floor is by ground do so
    if(!startFromEnd){
        Floor* current = m_ground;
        Floor* previous = nullptr;

        while (current != nullptr){ // iterate threw the list
            if (current->m_floorNum == floor){ // if it finds the floor, delete it
                if (current->m_next != nullptr)  // if the floor has a next bridge the gap
                    current->m_next->m_previous = previous;
                if (previous != nullptr) // if the floor has a previous bridge the gap
                    previous->m_next = current->m_next;
                delete current; // delete the current
                return true;
            }

            previous = current;
            current = current->m_next;

        }
    } else { // otherwise start from the end and delete in the same way just swaped pointers
        Floor* current = m_top;
        Floor* next = nullptr;

        while (current != nullptr){
            if (current->m_floorNum == floor){
                if (current->m_previous != nullptr)
                    current->m_previous->m_next = next;
                if (next != nullptr)
                    next->m_previous = current->m_previous;
                delete current;
                return true;
            }

            next = current;
            current = current->m_previous;

        }
    }
    return false; // if it gets here somthing went wrong
}
bool Elevator::insertFloor(int floor){
    if(m_ground == nullptr) // if list is empty throw an error
        throw "EMPTY ELEVATOR LIST";

    if(m_ground->m_floorNum > floor || m_top->m_floorNum < floor) // if its out of range throw an error
        throw out_of_range("INDEX OUT OF RANGE");

    // find the middle
    int middle = abs(m_ground->m_floorNum - m_top->m_floorNum)/2;
    bool startFromEnd = true;
    if(floor <= (m_ground->m_floorNum + middle))
        startFromEnd = false;



    if(!startFromEnd){ // if the floor number is closer to the beginning start from the beginning
        Floor* current = m_ground;
        Floor* previous = nullptr;

        while (current != nullptr){

            if (floor < current->m_floorNum){ //if its less than the one after it add it before
                if (current == m_ground){ // if we are at the beginning just insert at head
                    return insertAtHead(floor);
                }
                // otherwise create a new floor and update pointers
                Floor* newFloor = new Floor(floor);
                newFloor->m_next = current;
                current->m_previous = newFloor;
                newFloor->m_previous = previous;
                previous->m_next = newFloor;
                return true;
            }
            if (current->m_floorNum == floor){  // if it finds a duplicate floor throw an error
                throw "DUPLICATE FLOOR";
            }

            previous = current;
            current = current->m_next;

        }
    } else { // if its closer to the end do the same thing just with swapped pointers
        Floor* current = m_top;
        Floor* next = nullptr;

        while (current != nullptr){

            if (floor > current->m_floorNum){
                if(current == m_top){
                    return insertAtTail(floor);

                }
                Floor* newFloor = new Floor(floor);
                newFloor->m_previous = current;
                current->m_next = newFloor;
                newFloor->m_next = next;
                next->m_previous = newFloor;
                return true;
            }
            if (current->m_floorNum == floor){
                throw "DUPLICATE FLOOR";
            }


            next = current;
            current = current->m_previous;

        }
    }
    return false;
}
bool Elevator::checkFloor(int floor){
    if (floor < m_ground->m_floorNum || floor > m_top->m_floorNum) // if its out of range immediately return false
        return false;

    Floor* current = m_ground;

    while (current != nullptr){ // loop though the list
        if (current->m_floorNum == floor) // if it finds the floor return true
            return true;

        current = current->m_next;
    }

    return false;
}
bool Elevator::move(int origin, int destination){
    if (!checkFloor(origin) || !checkFloor(destination)){ // make sure the origin and destination both exist
        throw "ORIGIN OR DESTINATION DOESNT EXIST";
    }

    if((origin - destination) == 0) // make sure the origin and destination are different
        throw "ORIGIN AND DESTINATION THE SAME";

    // find middle
    int middle = abs(m_ground->m_floorNum - m_top->m_floorNum)/2;
    bool startFromEnd = true;
    if(origin <= (m_ground->m_floorNum + middle))
        startFromEnd = false;

    Floor* current = startFromEnd? m_top : m_ground; // decide weather current is top of ground based on bool
    Floor* destinationFloor = nullptr;

    while (current->m_floorNum != origin){ // find the origin floor
        if (current->m_floorNum == destination){ // if it finds the destiniation floor on the way store it
            destinationFloor = current;
        }
        if(startFromEnd){
            current = current->m_previous;
        } else {
            current = current->m_next;
        }
    }

    if (current->m_passenger.empty()) // if the floor is empty throw an error
        throw "NO ONE ON FLOOR";

    string passengerName = current->m_passenger; //store the name
    current->m_passenger = ""; //  set the floor to empty

    if(destinationFloor != nullptr){
        destinationFloor->m_passenger = passengerName;
        return true;
    }

    bool goUp = true;
    if((destination - current->m_floorNum) < 0) // decide weather to go up or down from that floor
        goUp = false;

    destinationFloor = current;
    while (destinationFloor->m_floorNum != destination){ // iderate up or down from the origin to find the destination
        if(goUp){
            destinationFloor = destinationFloor->m_next;
        } else {
            destinationFloor = destinationFloor->m_previous;
        }
    }

    // when it finds the floor put the passenger in it
    destinationFloor->m_passenger = passengerName;
    return true;

}
string Elevator::exit(int floor, string passenger){
    if(!checkFloor(floor)){ // if doent exist throw an error
        throw "FLOOR DOESNT EXIST";
    }
    // find the middle and set the start to top or ground depending on what is closer
    int middle = abs(m_ground->m_floorNum - m_top->m_floorNum)/2;
    bool startFromEnd = true;
    if(floor <= (m_ground->m_floorNum + middle))
        startFromEnd = false;

    Floor* current = startFromEnd? m_top : m_ground;

    // find the floor
    while (current->m_floorNum != floor){
        if(startFromEnd){
            current = current->m_previous;
        } else {
            current = current->m_next;
        }
    }

    // if the floor has the passenger we are looking for return the passenger and set the floor to have no passenger
    if(current->m_passenger == passenger){
        current->m_passenger = "";
        return passenger;
    } else if(current->m_passenger.empty()){
        return "";
    }

    return "";
}
bool Elevator::enter(int floor, string passenger){
    if(!checkFloor(floor)){ // if the floor doesnt exist throw an error
        throw "FLOOR DOESNT EXIST";
    }

    // find the middle and find the fastest route to the floor
    int middle = abs(m_ground->m_floorNum - m_top->m_floorNum)/2;
    bool startFromEnd = true;
    if(floor <= (m_ground->m_floorNum + middle))
        startFromEnd = false;

    Floor* current = startFromEnd? m_top : m_ground;

    while (current->m_floorNum != floor){
        if(startFromEnd){
            current = current->m_previous;
        } else {
            current = current->m_next;
        }
    }
    // if the floor is empty add the passenger if not return false
    if(current->m_passenger.empty()){
        current->m_passenger = passenger;
        return true;
    } else {
        return false;
    }

}
// copy constuctor
Elevator::Elevator(const Elevator & rhs){
    // set current and make sure m_ground and m_top are inisilized in case the list where copying is empty.
    Floor* current = rhs.m_ground;
    m_ground = nullptr;
    m_top = nullptr;
    // define new memory for each floor
    while (current != nullptr){
        insertAtTail(current->m_floorNum, current->m_passenger);
        current = current->m_next;
    }

}

const Elevator & Elevator::operator=(const Elevator & rhs){
    if(this == &rhs) // self assignment check
        return *this;
    clear(); //  clear any data already pressent
    Floor* current = rhs.m_ground;

    // define new memory for each floor
    while (current != nullptr){
        insertAtTail(current->m_floorNum, current->m_passenger);
        current = current->m_next;
    }
    return *this;
}
void Elevator::dump(){
    if (m_top != nullptr){
        Floor *temp = m_top;
        cout << "Top Floor " ;
        while(temp->m_previous != nullptr){
            cout << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
            temp = temp->m_previous;
        }
        cout << "Ground Floor " << temp->m_floorNum << " (" << temp->m_passenger << ")" << endl;
    }
}