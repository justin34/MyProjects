#include "Person.h"

// Name: Person
// Desc - Default Constructor for a Person
// Preconditions - Creates a Person with no data associated with it
// Postconditions - a Person is created
Person::Person() {
    m_ID = 0;
    m_age = 0;
    m_fName = "undefined";
    m_lName = "undefined";
    m_friendCount = 0;
}
// Name: Person
// Desc - Overloaded Constructor for a Person
// Preconditions - Creates a Person with passed data
// Postconditions - a Person is created
Person::Person(string fname, string lName, int age, int id) {
    m_fName = fname;
    m_lName = lName;
    m_age = age;
    m_ID = id;
    m_friendCount = 0;
}
// Name: AddFriend
// Desc - A person pointer is stored from the roster of people in an organization
// Preconditions - A person pointer is passed
// Postconditions - A person pointer is added to this person's m_friend's array
//                  if not at maximum and not already in the array
void Person::AddFriend(Person *person) {
    if(CheckID(person->m_ID)){
        cout << person->m_fName << " is already in your list" << endl;
        return;
    }

    if (m_friendCount == MAX_FRIENDS){
            cout << "You have reached the maximum number of friends" << endl;
            return;
    }
    m_friends[m_friendCount] = person;
    cout << m_friends[m_friendCount]->m_fName << " " << m_friends[m_friendCount]->m_lName <<
    " was added to friends list" << endl;
    m_friendCount++;

}
// Name: RemoveFriend
// Desc - Removes a person pointer from this person's m_friend array
// Preconditions - Person pointer exists in m_friend
// Postconditions - Person is removed from m_friend and all pointers are moved towards front
void Person::RemoveFriend() {
    if (m_friendCount == 0){
        cout << "You dont have any friends" << endl;
        return;
    }
    int choice;
    DisplayFriends();
    cin >> choice;
    while (choice > m_friendCount+1 || choice < 0){
        cin.clear();
        cin.ignore(123, '\n');
        cin >> choice;
    }

    for(int i = choice-1; i < m_friendCount; i++){
        m_friends[i] = m_friends[i+1];
    }
    m_friendCount--;


}
// Name: CheckID
// Desc - Checks to see if a specific person ID exists in m_friends - Note: IDs will always be unique in proj2
// Preconditions - m_friends is populated
// Postconditions - Returns true if id exists in m_friends else false
bool Person::CheckID(int id) {

    for(int i = 0; i < m_friendCount; i++){
        if(m_friends[i]->m_ID == id){
            return true;
        }
    }

    return false;
}
// Name: DisplayFriends
// Desc - Displays information about each friend in the m_friend array
// Preconditions - People are in the m_friend array
// Postconditions - Displays information about person object in array
void Person::DisplayFriends(){
    if (m_friendCount == 0){
        cout << "You have no friends" << endl;
        return;
    }

    for (int i = 0; i < m_friendCount; i++){
        cout << i+1 << ". ";
        m_friends[i]->DisplayDetails();
    }
}
// Name: DisplayDetails
// Desc - Displays information about this person
// Preconditions - Person data is populated
// Postconditions - Displays information about person object
void Person::DisplayDetails(){
    cout << m_fName << " " << m_lName << " (" << m_age << ") " << m_ID << endl;
}
// Name: SetDetails
// Desc - Used as a setter for first name, last name, age, and id
// Preconditions - Person already created
// Postconditions - Member variables populated
void Person::SetDetails(string fName, string lName, int age, int id){
    m_fName = fName;
    m_lName = lName;
    m_age = age;
    m_ID = id;
}