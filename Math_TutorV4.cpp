#include <iostream> //  for cin/cout
#include <string>   //  needed for string data types
#include <cstdlib>  // for generating random numbers
#include <ctime>    // include the time library
#include <cctype>   // for isalpha
#include <limits>   // to use numeric_limits
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    const int MAX_ATTEMPS = 3;
    const int LEVEL_RANGE_CHANGE = 10;

    enum MathType { MT_ADD, MT_SUBTRACT, MT_MULTIPLY, MT_DIVIDE };
    MathType questionType;

    int leftNum = 0;
    int rightNum = 0;
    int lessThanNum = 0;
    int userAns = 0;
    int correctAns = 0;
    int totalCorrect = 0;
    int totalIncorrect = 0;
    int currentLevel = 1;
    int currentRange = LEVEL_RANGE_CHANGE;

    char mathSymbol = '0';
    string userName = "unknown";
    string userInput = "unknown";

    // Vector to store question data for summary report
    vector<vector<int>> questions;
    srand(time(0));

    // display the program header
    cout << "***********************************************************" << endl;
    cout << "   *       Welcome to the silly simple math tutor!     *" << endl;
    cout << "***********************************************************" << endl;
    cout << "What is your name? ";
    getline(cin, userName);
    cout << "Welcome " << userName << " to the silly simple math tutor!" << endl;

    do {
        // Generate random numbers based on current range
        leftNum = rand() % currentRange + 1;
        rightNum = rand() % currentRange + 1;
        questionType = static_cast<MathType>(rand() % 4);

        // Determine the correct answer and math symbol based on question type
        switch (questionType) {
            case MT_ADD:
                correctAns = leftNum + rightNum;
                mathSymbol = '+';
                break;
            case MT_SUBTRACT:
                if (leftNum < rightNum) swap(leftNum, rightNum);
                correctAns = leftNum - rightNum;
                mathSymbol = '-';
                break;
            case MT_MULTIPLY:
                correctAns = leftNum * rightNum;
                mathSymbol = '*';
                break;
            case MT_DIVIDE:
                correctAns = leftNum;
                leftNum *= rightNum;
                mathSymbol = '/';
                break;
        }

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
                break;
            } else {
                if (i == MAX_ATTEMPS) {
                    cout << "\tIncorrect! The correct answer was " << correctAns << endl;
                    totalIncorrect++;
                } else {
                    cout << "\tIncorrect! You have " << MAX_ATTEMPS - i << " attempts left." << endl;
                }
            }

        }
        // Store the question data (level, leftNum, operator, rightNum, correctAns, attempts)
        questions.push_back({currentLevel, leftNum, mathSymbol, rightNum, correctAns});

        // Level adjustment based on total correct/incorrect answers
        if (totalCorrect == 3) {
            currentLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            currentRange += LEVEL_RANGE_CHANGE;
            cout << "Congrats! You are now at [Level " << currentLevel << "]!" << endl;
        } else if (totalIncorrect == 3 && currentLevel > 1) {
            currentLevel--;
            currentRange -= LEVEL_RANGE_CHANGE;
            totalCorrect = 0;
            totalIncorrect = 0;
            cout << "Sorry! You are now at [Level " << currentLevel << "]. Try again!" << endl;
        }

        // Ask if the user wants another question
        cin.ignore();  // Clear newline character from buffer
        while (true) {
            cout << "Do you want to try another question? (y=yes | n=no): ";
            getline(cin, userInput);
            for (char &c : userInput) c = tolower(c); // Convert input to lowercase
            if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no") break;
            cout << "Invalid input. Please try again." << endl;
        }

    } while (userInput == "y" || userInput == "yes");

    // Display the summary report after user chooses not to continue
    cout << "====================================" << endl;
    cout << "           Summary Report           " << endl;
    cout << "====================================" << endl;
    cout << setw(10) << left << "Level"
         << setw(15) << left << "Question"
         << setw(10) << left << "Attempts" << endl;
    cout << "------------------------------------" << endl;

    for (const auto &q : questions) {
        int questionLevel = q[0];
        int qLeftNum = q[1];
        char qMathSymbol = static_cast<char>(q[2]);
        int qRightNum = q[3];
        int qCorrectAns = q[4];
        int qAttempts = q[5];

        cout << setw(10) << left << questionLevel
             << setw(6) << left << qLeftNum << " " << qMathSymbol << " " << setw(6) << left << qRightNum
             << setw(10) << right << qAttempts << endl;
    }

    cout << "Thank you for using the silly simple math tutor!" << endl;
    return 0;
}
