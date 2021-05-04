// Instructions
// 
// Implement a code breaking game as a console application. At the beginning of the game, it randomly generates a secret 4 digit code.
// Each digit should be unique. For example, 0123, 9548, and 3217 are valid codes, but 1102, 4445, and 7313 are not.
//
// Once the number has been generated, the player has 8 chances to guess the code. After each guess, the game should report how many digits
// they guessed correctly, and how many had the right number, but in the wrong place. For example, with a secret code of 0123, a guess of 0451
// has one digit correct (the 0), and one digit with the right number in the wrong place (the 1).
// 
// After the player has either correctly broken the code or run out of guesses, ask if they would like to play again. If so, generate a new
// code and start again, otherwise exit the program.
//
// If the player enters a code that isn't valid, prompt them to try again but do NOT count the invalid guess as one of the 8 attempts. Also be sure that
// your game can handle any unexpected inputs without crashing.
//
// All your code should go in this file. Please do NOT include your name, as we anonymize tests during evaluation to reduce bias.
//
// Good luck!
#include<iostream>
#include<algorithm>
#include<vector>
#include<ctype.h>

using namespace std;

vector<int> createCode();
bool inputCheck(string input);

int main() {
    vector<int> code = createCode();
    cout << "Welcome to CodeBreaker." << endl;
    cout << '\n';
    cout << "<---------------------------------------->" << endl;
    cout << '\n';
    cout << "You have 8 chances to guess the 4 digit code. All digits will be unique." << endl; 
    cout << "A valid guess is a 4 digit number with no repeating digits. All invalid guesses will be ignored." << endl;
    
    string userGuess;
    while(cin >> userGuess){
    //checking for valid input
        if (inputCheck(userGuess)){
            cout << "thats a proper code ****" << endl;
            /*
                enter code checking part of program


            */
        }
    }
    return 0;
} 

vector<int> createCode() {
    vector<int> code;
    srand(time(0));
    while (code.size() < 4)
    {
        int digit = rand() % 10;
        if (find(code.begin(), code.end(), digit) == code.end()){
            code.push_back(digit);
        }
    }
    return code;
}

bool inputCheck(string userGuess) {
    if (userGuess.length() != 4 || !isdigit(userGuess[0]) || !isdigit(userGuess[1]) || !isdigit(userGuess[2]) || !isdigit(userGuess[3])) {
        cout << "Please enter a valid code" << endl;
        return false;
    }
    for(int i = 0; i < 4; i++) {
        int matchCount = 0;
        for(int y = 0; y < 4; y++){
            if (userGuess[i] == userGuess[y]){
                matchCount += 1;
            }
        }
        if (matchCount > 1){
            cout << "Please enter a valid code" << endl;
            return false;
        }
    }
    return true;
}
