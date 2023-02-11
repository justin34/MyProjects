
#include "FriendFinder.h"

// Name: FriendFinder
// Desc - Default constructor for application for finding friends
// Preconditions - Creates a Person and an organization
// Postconditions - Welcomes user and calls Start()
FriendFinder::FriendFinder() {
    cout << "*****************************\n"
            "Welcome to UMBC Friend Finder\n"
            "*****************************" << endl;

    Start();

}
// Name: GetDetails
// Desc - Asks   user for their first name, last name, age, and ID to populate m_me
// Preconditions - None
// Postconditions - Populates information related to m_me
void FriendFinder::GetDetails(){
    string name, lname;
    int age, id;
    cout << "What is your first name?" << endl;
    cin >> name;
    cout << "What is your last name?" << endl;
    cin >> lname;
    cout << "Whats your age?" << endl;
    cin >> age;
    cout << "WHats your id?" << endl;
    cin >> id;

    m_me = Person(name, lname, age, id);
}
// Name: DisplayMenu
// Desc - Displays main menu for application
// Preconditions - None
// Postconditions - Called from Start updates integer passed
void FriendFinder::DisplayMenu(int &choice){
    cin >> choice;
    while (cin.fail() || choice > 5 || choice < 0){
        cin.ignore(123,'\n');
        cin.clear();
        cin >> choice;
    }
}
// Name: Start
// Desc - Main function running FriendFinder
//        Calls GetDetails
//        Populates data for organization
//        Continually calls DisplayMenu until someone enters 4 (exit)
// Preconditions - m_me and m_organization are created but not populated
// Postconditions - Runs until user enters 4. Thanks user for usage. Ends application
void FriendFinder::Start(){
    GetDetails();
    Organization organization;
    organization.LoadRoster();
    int choice = 0;
    while (choice < 5){
        if (choice == 1) {
            cout << "You are: ";
            m_me.DisplayDetails();
            organization.DisplayRoster();
        }
        if (choice == 2) {
            m_me.DisplayFriends();

        }    if (choice == 3) {
            m_me.AddFriend(organization.GetPerson());

        }   if (choice == 4) {
            m_me.RemoveFriend();
        }

        cout << "What would you like to do?\n"
             "1. Display Entire Organization\n"
             "2. Display Friend List\n"
             "3. Search for a Friend\n"
             "4. Remove Friend\n"
             "5. Exit" << endl;

        DisplayMenu(choice);

    }
}

