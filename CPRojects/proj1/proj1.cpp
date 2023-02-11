#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

// global constants
const int boardSize = 15;
const int numberOfWords = 12;

// function prototypes
 void display(string board[][boardSize], string words[], int numberOfWordsLeft); // prints the board and the words below it
 string makeChoice(string board[][boardSize]); // Finds the word the user in trying to form and returns it
 bool isInlist(string word, string words[], int numberOfWordsLeft); // checks if the word provided is in the list
 void playGame( string board[][boardSize], string words[], int actualNumberOfWords); // handles the logic of the game
 void removeWord(string, string words[], int numberOfWordsLeft); // removes a word from the list

int main() {
    string board[boardSize][boardSize]; // stores board as a 2d array
    string words[numberOfWords]; // stores the words
    int actualNumberOfWords = 0; // stores how name words are in the array
    string fileName;
    // reads file and initializes arrays brackets are there so I could code fold
    {
        cout << "Whats the name of the file you want to add?" << endl;
        cin >> fileName;

        fstream file;

        file.open(fileName);
        string line;

        int x = 0; // line counter
        while (getline(file, line)) {

            if (x < boardSize) { // makes sure the line number is less than the size of the board
                int v = 0; // letter counter
                for (unsigned int i = 0; i < line.size(); i++) { // iterates over the whole line
                    if (line[i] != '\t' && line[i] != '\n') { // checks if the line part is a letter
                        board[x][v] = line[i]; // adds letter to the list
                        v++;
                    }
                }
                x++;
            } else { // if its past the board it adds the line to the words array

                for (unsigned int i = 0; i < line.size(); i++) {
                    if (line[i] != '\n') // makes sure it doesnt add the \n character to the word
                        words[x - 15] += line[i];
                }

                x++;
            }

        }

        for (int i = 0; i < numberOfWords; i++){ // iterates over the word list
            if (!words[i].empty()) // only counts if there is a word in the array index
                actualNumberOfWords++;
        }
    }

    playGame(board,words, actualNumberOfWords); // plays the game

}

void display(string board[][boardSize], string words[], int numberOfWordsLeft){
    for(int i = -1; i < boardSize; i++){ // iterates over the board + 1 for the numbers
        if (i < 0) { // if its on the number row
            for (int x = 0; x < boardSize + 1; x++) {
                if (x == 0) { // if its at the beginning add a tab
                    cout << "\t";
                } else { // otherwise add the numbers in assending order from 0
                    cout << x - 1 << "\t";
                }
            }
            cout << endl;
        } else {
            cout << i << "\t"; // print the number in the beginning of the row
            for (int x = 0; x < boardSize; x++){ // print the row of letters
                cout << board[i][x] << "\t";
            }
            cout << endl; // add a \n at the end
        }
    }
    cout << "----------" << "Words" << "----------" << endl;
    for(int i = 0; i < numberOfWordsLeft; i++){ // prints out words
        cout << words[i] << endl;
    }
}
string makeChoice(string board[][boardSize]){
    int a,b; // stores the numeric value of the first choice
    string choice; // stores the "X Y" 1
    int c,d; // stores the numeric value of the first choice
    string choice2; // stores the "X Y" 2

    cout << "What is the starting X Y (separated by a space)?" << endl;
    getline(cin >> ws, choice); // gets the whole line including White space
    cout << "What is the ending X Y (separated by a space)?" << endl;
    getline(cin >> ws, choice2);

    if (!choice.empty()) { // if there is a choice
        int i = 0; // counter of iteration of choice
        string num; // string of num1
        string num2;

        while (choice[i] != ' ') { // stores the number into num untill it gets to a space
            num += choice[i];
            i++;
        }

        i++; // skip over the space
        while (choice[i]) { // stores number until there is no number to store
            num2 += choice[i];
            i++;
        }

        b = stoi(num); // converts form type string to int
        a = stoi(num2);
    } else { return " ";}

    if (!choice2.empty()) { // same as first
        int i = 0;
        string num;
        string num2;

        while (choice2[i] != ' ') {
            num += choice2[i];
            i++;
        }

        i++;
        while (choice2[i]) {
            num2 += choice2[i];
            i++;
        }

        d = stoi(num);
        c = stoi(num2);
    } else { return " ";}

    string word; // word that will be returned
    if( a == c && b == d) // if the points are the same it returns nothing
        return word;

    // finds slope
    int rise = d - b;
    int run = c - a;

    if (a == c){ // if the horizontal values are the same
        // the two if statments decide if we move left of right
        if(b < d){
            for (int i = b; i <= d; i++){
                word += board[i][a]; // puts each letter into the word
            }
        }

        if(b > d){
            for (int i = b; i >= d; i--){
                word += board[i][a];
            }
        }
    }

    if (b == d) { // same as above but up and down
        if(a < c){
            for (int i = a; i <= c; i++){
                word += board[b][i];
            }
        }

        if(a > c){
            for (int i = a; i >= c; i--){
                word += board[b][i];
            }
        }
    }

    if (abs(rise) == abs(run)){// if the slope is 1
        int aChange = a < c ? 1: -1; // decides if we have to move left or right
        int cChange = b < d ? 1: -1; // decides if we have to move up or down

        int v = b;
        for (int i = a; i != c + (1 * aChange); i += (1 * aChange)){ // iterates until the points a,b gets too c+-1,d+-1
            word += board[v][i]; // adds each letter to word
            v += 1 * (cChange);
        }


    }
    cout << word << endl;

    return word;
}
bool isInlist(string word, string words[], int numberOfWordsLeft) { // returns true if the ord is in the list
    for (int i = 0; i < numberOfWordsLeft; i++){
        if (word == words[i])
            return true;
    }
    return false;
}
void playGame( string board[][boardSize], string words[], int actualNumberOfWords) {
    int numberOfWordsLeft = actualNumberOfWords;
    int guessedRight = 0;
    string wordsGuessed[numberOfWords];

    while (numberOfWordsLeft > 0){ // loop until you guess all the words
        display(board, words, numberOfWordsLeft); // displays game
        string choice = makeChoice(board); // asks user to make find a word and stores it in choice

        if(isInlist(choice, words, numberOfWordsLeft)){ // checks if that word is in the word list
            cout << "You found the word: " << choice << endl; // tells the user that they found a word
            wordsGuessed[guessedRight] = choice;
            guessedRight++;
            removeWord(choice, words, numberOfWordsLeft); // removes the word from the word list
            numberOfWordsLeft--;
        }
    }

    cout << "YOU WIN! Thank you for playing." << endl;
}
void removeWord(string word, string words[], int numberOfWordsLeft){
    string newWords[numberOfWordsLeft];
    int v = 0;
    for (int i = 0; i < numberOfWordsLeft; i++){
        if (words[i] != word) {
            newWords[v] = words[i];
            v++;
        }
    }
    for (int i = 0; i < numberOfWordsLeft; i++){
            words[i] = newWords[i];
    }
}

