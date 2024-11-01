/*********************************************************************************
Program: MathTutor
  Programmers: Jacob Ferguson & Alejandro Rivera
  Date: 10/16/24
  GitHub URL: https://github.com/thesolejacobf/MathTutor_V3
  Description: This program is intended to be a math tutor design for a younger
  audience. As of V3, It'll generate two random numbers between a set range that is
  determined by the current level that the user is at (i.e A # with a max of 10 to a
  number with a max of 20), using the system clock as the seed, generate a random
  operator, do the math with both the random numbers and the operator to produce a
  correct answer. After this, the program displays an intro screen with a title, and
  some "Facts", after this, the program gets the user's full name via getline, and
  then introduce the player to the program. Afterward, the program uses the previously
  generated numbers to provide a question for the user to answer, afterward, the
  program will compare the user's input to the result of the machine answered question.
  Also included is error handling in the event that the program generates an impossible
  math operator, as well as if the user enters a non-integer response to a question.
  This program, over the course of the user answering questions, will increase or
  decrease to a different "Level" based on the amount of questions the
  user gets right/wrong. The user get 3 attemps at every question, and if they fail
  3 different questions, they level down. This also applies vice versa.
**********************************************************************************/
#include <iostream> //  for cin/cout
#include <string>   //  needed for string data types
#include <cstdlib>// for generating random numbers
#include <ctime> //include the time library
#include <cctype> // for isalpha
#include <limits> //to use numeric_limits
#include <vector>
#include <iomanip>

using namespace std; // so you dont have to type std:: in front of cin/cout/endl

int main() {
    // declare and intialize the variables
    const int MAX_ATTEMPS = 3;
    const int LEVEL_RANGE_CHANGE = 10;

    enum MathType { MT_ADD, MT_SUBTRACT, MT_MULTIPLY, MT_DIVIDE };
    MathType questionType;

    int leftNum = 0;
    int rightNum = 0;
    int lessThanNum = 0; // This is used in the math problems to prevent neg. numbers
    int userAns = 0;
    int correctAns = 0;
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int currentLevel = 1; // Is used to make sure it starts at level 1
    int currentRange = LEVEL_RANGE_CHANGE; //This stores the current range of the math problems
    int attempts = 0;

    char mathSymbol = '0';

    string userName = "unknown"; // this will store the user's name entered
    string userInput = "unknown"; // Used to hold user's input to continuing the program

    vector<vector<int>> questions;

    srand(time(0));

    // display the program header
    cout << "***********************************************************" << endl;
    cout << " __  __       _   _   _____      _             " << endl;
    cout << "|  \\/  | __ _| |_| |_|_   _|   _| |_ ___  _ __ " << endl;
    cout << "| |\\/| |/ _` | __| '_ \\| || | | | __/ _ \\| ‘__|" << endl;
    cout << "| |  | | (_| | |_| | | | || |_| | || (_) | |  " << endl;
    cout << "|_|  |_|\\____|\\__|_| |_|_| \\____|\\__\\___/|_|  " << endl;
    cout << endl;
    cout << "***********************************************************" << endl;
    cout << "   *       Welcome to the silly simple math tutor!     *" << endl;
    cout << "***********************************************************" << endl;
    cout << endl;

    // displays the math jokes and facts
    cout << "Funny math jokes and facts: " << endl;
    cout << endl;
    cout << "  * The product of any even number times two is always even!" << endl;
    cout << endl;
    cout << "  * Every even number times two is always divisible by four!" << endl;
    cout << endl;
    cout << "  * If you're cold, go to the corner of the room. It's 90 degrees "
            "there! " << endl;
    cout << endl;
    cout << "  * Why is 69 so scared of 70? Because once they fought, and 71." << endl;
    cout << endl;
    cout << "***********************************************************" << endl;
    cout << endl;

    // Gets the user's name and welcomes the user
    cout << "What is your name? ";
    getline (cin, userName);
    // After the user types their name, the program will display a welcome message
    cout << "Welcome " << userName << " to the silly simple math tutor!" << endl;

    do { // Beginning of the do while loop that allows for the attempts system to work
        leftNum = rand() % (currentRange) + 1; //Assign random numbers to the variable left num between 1 and 10 inclusive
        rightNum = rand() % (currentRange) + 1; //Assign random numbers to the variable right num between 1 and 10 inclusive
        // math_type = rand()%(4) + 1; //Assign random numbers to the variable math type between 1 and 4 inclusive
        questionType = static_cast<MathType>(rand() % 4); // generates a random number from 0 to 3

        // Handles the math type, and produces both a correct answer and a math symbol for the question
        switch (questionType) {
            case MT_ADD:
                correctAns = leftNum + rightNum;
                mathSymbol = '+';
                break;
            case MT_SUBTRACT:
                // Ensures that the leftNum is always greater than the rightNum, preventing negatives
                if (leftNum < rightNum) {
                    lessThanNum = rightNum;
                    leftNum = rightNum;
                    rightNum = lessThanNum;
                }
                correctAns = leftNum - rightNum;
                mathSymbol = '-';
                break;
            case MT_MULTIPLY:
                correctAns = leftNum * rightNum;
                mathSymbol = '*';
                break;
            case MT_DIVIDE:
                // Ensure that the left number is greater than the right number, and divisible
                correctAns = leftNum;
                leftNum *= rightNum;
                mathSymbol = '/';
                break;
        }

        vector<int> row = {currentLevel, leftNum, mathSymbol, rightNum, correctAns};

        for(int i = 0; i < questions.size(); i++) {
            currentLevel = questions[i].at(0);
            leftNum = questions[i].at(1);
            mathSymbol = static_cast<char>(questions[i].at(2));
        }
        // Check the user's answer & handles the leveling count
        for (int i = 1; i <= MAX_ATTEMPS; i++) {
            cout << "[Level #" << currentLevel << "] ";
            cout << userName << ", what is " << leftNum << " " << mathSymbol << " " << rightNum << "? ";

            // Loop until the user enters numeric data
            while (!(cin >> userAns)) {
                cin.clear(); // clear the cin error flag
                // need to include the limits library to use numeric limits
                cin.ignore(numeric_limits<streamsize>::max(),
                           '\n'); //ignore the max input, up to '\n'
                cout << "\tInvalid input?" << endl;
                cout << "\tPlease enter a number: ";
            } // end of get userAnswer while loop

            // Announces to the user if their answer was correct or incorrect, and handles the attempts
            if (userAns == correctAns) {
                cout << "\tCorrect!" << endl;
                totalCorrect++;
                row.push_back(i);
                break;
            } else {
                ///row.push_back()
                if (i == MAX_ATTEMPS) {
                    cout << "\tIncorrect! The correct answer was " << correctAns << endl;
                    row.push_back(0);
                    totalIncorrect++;
                } else {
                    cout << "\tIncorrect! You have " << MAX_ATTEMPS - i << " attempts left." << endl;
                }
            }
        }

        questions.push_back(row);

        // Handles the leveling system. Increases with 3 correct answers and vice versa
        if (totalCorrect == 3) { // Increases user's level
            currentLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            currentRange = currentRange + LEVEL_RANGE_CHANGE;
            cout << endl;
            cout << "Congrats! You are now at [Level " << currentLevel << "]! ";
            cout << "Your new range has increased to: " << currentRange << "!" << endl;
        } else if (totalIncorrect == 3) {
            totalCorrect = 0;
            totalIncorrect = 0;
            if (currentLevel == 1) { // This prevents the user's level from going below 1
                cout << "We literally can't lower your level anymore. Please try again." << endl;
            } else { // Decreases user's level
                currentLevel--;
                currentRange -= LEVEL_RANGE_CHANGE;
                cout << "Sorry! You are now at [Level " << currentLevel << "]! " << "Try again! ";
                cout << "Your range has decreased to: " << currentRange << "!" << endl;
            }

        }

        //Clears the newline from the input buffer
        getline(cin, userInput);

        //Input for whether they want another question
        //validates y,yes,n,no
        while (true) {
            cout << endl;
            cout << "Do you want to try another question? (y=yes | n=no): ";
            getline(cin, userInput);
            //to lower case the users input
            for (int i = 0; i < userInput.size(); i++) {
                userInput.at(i) = tolower(userInput.at(i));
            }
            if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no") {
                break;
            } else {
                cout << "Invalid input. Please try again...." << endl;
            }
        }

    } while (userInput == "y" || userInput == "yes"); // End of the do while loop.

    cout << "====================================" << endl;
    cout << "           Summary Report           " << endl;
    cout << "====================================" << endl;
    cout << "Level       Question       Attempts " << endl;
    cout << "-----    --------------    -------- " << endl;
    totalCorrect = 0;
    totalIncorrect = 0;

    for (int i = 0; i < questions.size(); i++) {
        currentLevel = questions.at(i).at(0);
        leftNum = questions.at(i).at(1);
        mathSymbol = static_cast<char>(questions.at(i).at(2));
        rightNum = questions.at(i).at(3);
        correctAns = questions.at(i).at(4);
        attempts = questions.at(i).at(5);
        cout << "  " << setw(2) << left << currentLevel << "  " << setw(5) << left << leftNum;
    }


    cout << "Thank you for using the silly simple math tutor!" << endl; // bids the user farewell

    return 0;
}
