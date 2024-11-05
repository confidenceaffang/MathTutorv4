#include <iostream> //  for cin/cout
#include <string>   //  needed for string data types
#include <cstdlib>  // for generating random numbers
#include <ctime>    // include the time library
#include <cctype>   // for isalpha
#include <limits>   // to use numeric_limits
#include <vector>   // for assinging the vectors
#include <iomanip>  // for stying the display
#include <cmath>    //for rounding the average correct answers

using namespace std;

int main()
{
    const int MAX_ATTEMPS = 3;         // creates and initializes the maximum attempts
    const int LEVEL_RANGE_CHANGE = 10; // creates and initializes the changes in level range

    // sets math type as an enum
    enum MathType
    {
        MT_ADD,
        MT_SUBTRACT,
        MT_MULTIPLY,
        MT_DIVIDE
    };
    MathType questionType;

    int leftNum = 0;  // creates and initializes the left number
    int rightNum = 0; // creates and initializes the right number
    int lessThanNum = 0;
    int userAns = 0;                       // creates and initializes the user answer
    int correctAns = 0;                    // creates and initializes the correct answer
    int totalCorrect = 0;                  // creates and initializes the total correct answers
    int totalIncorrect = 0;                // creates and initializes the total incorect answers
    int currentLevel = 1;                  // creates and initializes the current level
    int currentRange = LEVEL_RANGE_CHANGE; // creates and initializes the range of values for current level
    int attempts = 0;                      // creates and initializes the number of attempts
    int sumTotalCorrect = 0;               // creates and initializes the sum total correct answers
    int sumTotalIncorrect = 0;             // creates and initializes the sum total incorrect answers
    int sumTotalQuestions = 0;             // creates and initializes the sum total questions asked
    double averageCorrect = 0;             // creates and initializes the average correct answers

    char mathSymbol = '0';        // assign mathSymbol
    string userName = "unknown";  // assign userName variable
    string userInput = "unknown"; // assign userInput

    // Vector to store question data for summary report
    vector<vector<int>> questions; // 2D vector for storing the data
    srand(time(0));                // generating random number in this program

    // Display heading and jokes
    cout << "***********************************************************" << endl;
    cout << " __  __       _   _   _____      _             " << endl;
    cout << "|  \\/  | __ _| |_| |_|_   _|   _| |_ ___  _ __ " << endl;
    cout << "| |\\/| |/ _` | __| '_ \\| || | | | __/ _ \\| ‘__|" << endl;
    cout << "| |  | | (_| | |_| | | | || |_| | || (_) | |  " << endl;
    cout << "|_|  |_|\\____|\\__|_| |_|_| \\____|\\__\\___/|_|  " << endl;
    cout << "***********************************************************" << endl;
    cout << "   *       Welcome to the silly simple math tutor!     *" << endl;
    cout << "***********************************************************" << endl;
    cout << endl;
    cout << "Funny math jokes and facts: " << endl;
    cout << "  * The product of any even number times two is always even!" << endl;
    cout << "  * Every even number times two is always divisible by four!" << endl;
    cout << "  * If you're cold, go to the corner of the room. It's 90 degrees there!" << endl;
    cout << "  * Why is 69 so scared of 70? Because once they fought, and 71." << endl;
    cout << "***********************************************************" << endl;
    cout << endl;
    cout << "What is your name? ";
    getline(cin, userName);
    cout << "Welcome " << userName << " to the silly simple math tutor!" << endl;

    do
    {
        // Generate random numbers based on current range
        leftNum = rand() % currentRange + 1;
        rightNum = rand() % currentRange + 1;
        questionType = static_cast<MathType>(rand() % 4);

        // Determine the correct answer and math symbol based on question type
        switch (questionType)
        {
        case MT_ADD:
            correctAns = leftNum + rightNum;
            mathSymbol = '+';
            break;
        case MT_SUBTRACT:
            if (leftNum < rightNum)
                swap(leftNum, rightNum);
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

        for (attempts = 1; attempts <= MAX_ATTEMPS; attempts++)
        {
            cout << "[Level #" << currentLevel << "] ";
            cout << userName << ", what is " << leftNum << " " << mathSymbol << " " << rightNum << "? ";
            sumTotalQuestions++;
            // Loop until the user enters numeric data
            while (!(cin >> userAns))
            {
                cin.clear(); // clear the cin error flag
                // need to include the limits library to use numeric limits
                cin.ignore(numeric_limits<streamsize>::max(),
                           '\n'); // ignore the max input, up to '\n'
                cout << "\tInvalid input?" << endl;
                cout << "\tPlease enter a number: ";
            } // end of get userAnswer while loop

            // Announces to the user if their answer was correct or incorrect, and handles the attempts
            if (userAns == correctAns)
            {
                cout << "\tCorrect!" << endl;
                totalCorrect++;
                sumTotalCorrect++;
                break;
            }
            else
            {
                if (attempts == MAX_ATTEMPS)
                {
                    cout << "\tIncorrect! The correct answer was " << correctAns << endl;
                }
                else
                {
                    cout << "\tIncorrect! You have " << MAX_ATTEMPS - attempts << " attempts left." << endl;
                }
                totalIncorrect++;
                sumTotalIncorrect++;
            }
        }
        // Store the question data (level, leftNum, operator, rightNum, correctAns, attempts)
        questions.push_back({currentLevel, leftNum, mathSymbol, rightNum, correctAns, attempts});

        // Level adjustment based on total correct/incorrect answers
        if (totalCorrect == 3)
        {
            currentLevel++;
            totalCorrect = 0;
            totalIncorrect = 0;
            currentRange += LEVEL_RANGE_CHANGE;
            cout << "Congrats! You are now at [Level " << currentLevel << "]!" << endl;
        }
        else if (totalIncorrect == 3 && currentLevel > 1)
        {
            currentLevel--;
            currentRange -= LEVEL_RANGE_CHANGE;
            totalCorrect = 0;
            totalIncorrect = 0;
            cout << "Sorry! You are now at [Level " << currentLevel << "]. Try again!" << endl;
        }
        else if (totalIncorrect == 3)
        {
            totalCorrect = 0;
            totalIncorrect = 0;
        }

        // Ask if the user wants another question
        cin.ignore(); // Clear newline character from buffer
        while (true)
        {
            cout << "Do you want to try another question? (y=yes | n=no): ";
            getline(cin, userInput);
            for (char &c : userInput)
                c = tolower(c); // Convert input to lowercase
            if (userInput == "y" || userInput == "yes" || userInput == "n" || userInput == "no")
                break;
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
    cout << "--------  -------------  ---------------" << endl;

    averageCorrect = (static_cast<double>(sumTotalCorrect) / static_cast<double>(sumTotalQuestions)) * 100;
    for (const auto &q : questions)
    {
        int questionLevel = q[0];
        int qLeftNum = q[1];
        char qMathSymbol = static_cast<char>(q[2]);
        int qRightNum = q[3];
        int qCorrectAns = q[4];
        int qAttempts = q[5];

        cout << setw(10) << left << questionLevel
             << setw(2) << left << qLeftNum << " " << qMathSymbol << " " << setw(2) << left << qRightNum
             << setw(2) << right << " = " << qCorrectAns << setw(11) << right << qAttempts << endl;
    }
    // print out summary work of questions answered
    cout << endl;
    cout << "Total Questions :" << sumTotalQuestions << endl;
    cout << "Total Correct: " << sumTotalCorrect << endl;
    cout << "Total Incorrect:  " << sumTotalIncorrect << endl;
    cout << "Average Correct: " << round(averageCorrect) << "%" << endl;
    cout << "Thank you for using the silly simple math tutor!" << endl;
    return 0;
}
