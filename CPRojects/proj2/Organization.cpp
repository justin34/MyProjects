#include "Organization.h"

// Name: Organization
// Desc - Default constructor for Organization
// Preconditions - None
// Postconditions - Organization is created (empty) with 0 people in the roster
Organization::Organization() {
    m_name = "";
    m_numRoster = 0;

}
// Name: SetName
// Desc - Sets m_name by asking user for name
// Preconditions - m_name exists
// Postconditions - Asks user for the organization name and populates m_name
void Organization::SetName(){
    cout << "Whats the name of the organization?: ";
    cin >> m_name;

}
// Name: LoadRoster
// Desc - Sets m_fileName by asking user. Then populates all of the people loaded from file
// Preconditions - m_fileName exists. m_roster empty
// Postconditions - Asks user for m_fileName. Loads data from file and populates m_roster
void Organization::LoadRoster(){
    fstream newfile;
    newfile.open(FILE_NAME, ios::in);
    cout << "atempting" << endl;
    if (newfile.is_open()){   //checking whether the file is open
        cout << "file is open" << endl;
        string name, lname, age, id;
        int rAge;
        int rId;
        int i = 0;
        while(i < MAX_PEOPLE){ //read data from file object and put it into strings.

            getline(newfile, name, ',');
            getline(newfile,lname,',');
            getline(newfile,age,',');
            getline(newfile,id,'\n');
            rAge = stoi(age);
            rId = stoi(id);
            Person person(name, lname, rAge, rId);
            m_roster[i] = person;
            m_numRoster++;
            i++;
        }

        cout << m_numRoster << " loaded to roster" << endl;
        newfile.close(); //close the file object.
    }
}
// Name: DisplayRoster
// Desc - Displays a numbered list of everyone in the roster (starts at 1)
// Preconditions - m_roster is populated
// Postconditions - Displays a numbered list of people
void Organization::DisplayRoster(){
    if (m_numRoster == 0)
        return;

    cout << "******" << m_name << "******" << endl;
    for(int i = 0; i < m_numRoster; i++){
        cout << i+1 << ". ";
        m_roster[i].DisplayDetails();
    }
}
// Name: GetPerson
// Desc - Displays a list of people in m_roster and user enters number of desired person.
//        Returns pointer of that person in m_roster
// Preconditions - m_roster is populated
// Postconditions - Returns pointer for the person chosen from list
Person* Organization::GetPerson(){
    int choice;
    DisplayRoster();
    cout << "Enter the number you want to add: ";
    cin >> choice;

    while(choice > m_numRoster && choice < 0){
        cin.ignore(123,'\n');
        cin.clear();
        cout << "Enter the number you want to add: ";
        cin >> choice;
    }

    return &m_roster[choice-1];
}
