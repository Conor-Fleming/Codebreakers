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

//compiled with "g++ ../CodeBreaker.cpp -std=c++11 -o output" on iOS

#include<iostream>
#include<algorithm>
#include<vector>
#include<ctype.h>

using namespace std;

//function declarations
vector<int> createCode();
bool inputCheck(string input);
bool codeCompare(vector<int> code, vector<int> validCode, int &guess);

int main() {
    //big while loop to help with easy re-running of program based on user input
    char replay = 'y';
    while(replay == 'y'){
        //creating code and beginning game, createCode() handles the creating of the random code 
        vector<int> code = createCode();
        cout << "\t\t\tWelcome to CodeBreaker." << endl;
        cout << '\n';
        cout << "\t\t<---------------------------------------->" << endl;
        cout << '\n';
        cout << "You have 8 chances to guess the 4 digit code. All digits will be unique." << endl; 
        cout << "A valid guess is a 4 digit number with no repeating digits. All invalid guesses will be ignored." << endl;
        string input;
        int guessCount = 0;
        bool correctGuess = false;
        while(cin >> input){
            //checking for valid input
            if (inputCheck(input)){
                //code will be valid so decalring vector and pushing individual digits into vector for easier comparison.
                vector<int> validCode;
                for(char const c: input){
                    validCode.push_back(c - '0');
                }
                //if code is guess codeCompare will return true
                correctGuess = codeCompare(code, validCode, guessCount);
            }
            //adding conditionals, if user guesses code they dont need to know it again.
            if(correctGuess)
                break;
            //unsuccessful guess displays the code to user then breaks out of while loop
            if(guessCount == 8){
                cout << "The code was " << code[0] << code[1] << code[2] << code[3];
                cout << ".\n";
                break;
            }
        }
        //asking user if they want to re-play, a 'y' response will re-trigger outer while loop
        cout << "Do you want to play again? (y/n):" << endl;
        cin >> replay;
    } 
    return 0;
} 

bool codeCompare(vector<int> code, vector<int> validCode, int &guessCount){
    int digitCorrect = 0;
    int digitWrongPos = 0;
    //if user guesses correctly display message and return with true flag.
    if(validCode == code){
        cout << "Congrats! You have guessed the code!" << endl;
        return true;
    //else for each digit of the user guess see if that digit exists in the code
    }else{
        for(int i = 0; i < code.size(); i++){
            vector<int>::iterator iter = find(code.begin(), code.end(), validCode[i]);

            //if the guessed digit exists in the code add 1 to correct guesses count and record index position
            if(iter != code.end()){
                digitCorrect++;
                int position = distance(code.begin(), iter);
                //checking if position of digit is correct
                if(position != i)
                digitWrongPos++;
            }
        }
        //incrementing guesses and display stats to user.
        cout << "You guessed " << digitCorrect << " correct number(s). " << digitWrongPos << " of which, in the wrong position" << endl;
        guessCount++;
        cout << 8 - guessCount << " guesses left." << endl;
    }
    return false;
}

vector<int> createCode() {
    vector<int> code;
    //seeding random number generator so it is different each iteration of game
    srand(time(0));
    //keeping code to 4 digits
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
    //making sure user doesnt enter a number longer than 4 digits or any non digit characters
    if (userGuess.length() != 4 || !isdigit(userGuess[0]) || !isdigit(userGuess[1]) || !isdigit(userGuess[2]) || !isdigit(userGuess[3])) {
        cout << "Please enter a valid code" << endl;
        return false;
    }
    //checking for repeat digits in user input
    //comparing each digit with the rest of the digits in string and incrementing counter when they are equivalent
    for(int i = 0; i < 4; i++) {
        int matchCount = 0;
        for(int y = 0; y < 4; y++){
            if (userGuess[i] == userGuess[y]){
                matchCount += 1;
            }
        }
        //if match count is greater than 1 (each digit will always be equal to itself) reject entered code
        if (matchCount > 1){
            cout << "Please enter a valid code" << endl;
            return false;
        }
    }
    return true;
}
