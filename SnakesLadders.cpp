//Include statements
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <random>
#include <thread>
#include <chrono>
#include <vector>

using namespace std;

//Variable declarations
const int boardSize = 100;      //Size of the array 
string board[boardSize];        //The 100th place on the map
string const TOP = "/-------------------------------------------------\\";
string const LEFT = "|----<----<----<----<----<----<----<----<----<    |";
string const RIGHT = "|    >---->---->---->---->---->---->---->---->----|";
string const BOTTOM = "\\-------------------------------------------------/";
string const MENU_MESSAGE_1 = "\n\n\tSnakes and Ladders\n\n\t1 - Play with a Bot\n\t2 - Play with a Friend\n\n\tEnter a number: ";
string const INVALID_ENTRY_1 = "\n\n\tSnakes and Ladders\n\n\t1 - Play with a Bot\n\t2 - Play with a Friend\n\n\tYour entry is invalid. Try again: ";
string const MENU_MESSAGE_2 = "\n\n\tSelect a Difficulty\n\n\t1 - Easy\n\t2 - Medium\n\t3 - Hard\n\n\tEnter a number: ";
string const INVALID_ENTRY_2 = "\n\n\tSelect a Difficulty\n\n\t1 - Easy\n\t2 - Medium\n\t3 - Hard\n\n\tYour entry is invalid. Try again: ";
int roll;       //Stores the value for the die
int p1 = 1;     //Initializes the location of player 1
int p2 = 1;     //Initializes the location of player 2
int menu1;      //Stores the return value of the first menu
map<int, int> Map;    //Stores the locations of the snakes and ladders and their respective sizes
vector<string> snakesVector;        //Stores messages that have the location and length of each snake
vector<string> laddersVector;        //Stores messages that have the location and length of each ladder

/* Defines the individual probabilities of the random number generator selecting 0-9.
The leftmost probability corresponds to 0 and the rightmost probability corresponds to 9. Probabilities must add to 1.0. */
double probabilities[] = {0.31, 0.19, 0.15, 0.115, 0.085, 0.06, 0.04,  0.025, 0.015, 0.01};
discrete_distribution<int> distribution(begin(probabilities), end(probabilities));     //Used to create a distribution where you can assign different probabilities to each possible outcome
mt19937 gen(time(0));       //Initializes the random number generator with the current time

//Function prototypes
void displayBoard();
int displayMenu1();
int displayMenu2();
void displayMenu3(string& play1, string& play2);
bool validateNumber(double num, string message);
void createSnakes();
void createLadders();
int rollDice();
void movePlayer1(string player1, string player2, char& wasSnakeOrLadder, int& ladderLength, int& snakeLength, int& newLocation);
void movePlayer2(string player1, string player2, char& wasSnakeOrLadder, int& ladderLength, int& snakeLength, int& newLocation);
char moveToLadder(int& p0, string player0, int& ladderLength, int& newLocation);
char moveToSnake(int& p0, string player0, int& snakeLength, int& newLocation);
void displayLengths();
void play();

int main()
{
    srand(time(0));     //Sets the seed of the rand function

    //fill the array
    for (int i = 0; i < boardSize; i++)
    {
        if (i < 9)
            board[i] = to_string(i + 1) + " ";
        else
            board[i] = to_string(i + 1);
    }

    createSnakes();
    createLadders();

    system("clear");        //Clears the screen
    menu1 = displayMenu1();
    play(); //I removed the rest prom the main function to play() function

    return 0;
}
int displayMenu1()
{
    cout << MENU_MESSAGE_1;     //Displays the first menu
    int number1;        //Stores the input of the first menu option
    bool loopAgain1;     //If true, the loop repeats

    do {
        do {
            cin >> number1;     //Here the user enters the input
        } while (validateNumber(number1, INVALID_ENTRY_1) == false);    //Makes sure the user enters an integer

        switch (number1)
        {
            case 1:
                return 1;
            case 2:
                return 2;
            default:
                system("clear");
                cout << INVALID_ENTRY_1;        //Displays a message indicating that the user entered an incorrect value
                loopAgain1 = true;
        }
    } while (loopAgain1 == true);     //If value is true, the loop repeats
    return 0;
}
int displayMenu2()
{
    cout << MENU_MESSAGE_2;       //Displays the second menu
    int number2;        //Stores the input of the second menu option
    bool loopAgain2;     //If true, the loop repeats

    do {
        do {
            cin >> number2;     //Here the user enters the input
        } while (validateNumber(number2, INVALID_ENTRY_2) == false);
        
        switch (number2)
        {
            case 1:
                return 1;
            case 2:
                return 2;
            case 3:
                return 3;
            default:
                system("clear");
                cout << INVALID_ENTRY_2;       //Displays a message indicating that the user entered an incorrect value
                loopAgain2 = true;
        }
    } while (loopAgain2 == true);     //If value is true, the loop repeats
    return 0;
}
void displayMenu3(string& play1, string& play2)
{
    cout << "\n\n\tEnter the name of Player 1: ";
    cin >> play1;

    system("clear");
    cout << "\n\n\tEnter the name of Player 2: ";
    cin >> play2;

}
void displayBoard()
{
    //Print the value at the top of the board
    cout << TOP << endl;

    //Define the positions for even and odd rows
    int even = 99;
    int odd = 80;

    //Loop through each row
    for (int rows = 1; rows <= 10; rows++)
    {
        //Check if the row is odd
        if (rows % 2 != 0)   //Odd rows 
        {
            //Print a vertical bar for odd rows
            cout << "| ";

            //Loop through 10 elements in reverse order and print corresponding values from the 'board' array
            for (int i = 0; i < 10; i++)
            {
                // Check if it's the first element of the row
                if (even == 99 && i == 0)
                {
                    cout << board[even] << "  ";
                    even = even - 1;
                }
                //Check if it's the last element of the row
                else if (i == 9)
                {
                    cout << board[even] << " ";
                    even = even - 1;
                }
                //For other elements in the row
                else
                {
                    cout << board[even] << "   ";
                    even = even - 1;
                }
            }

            // Adjust the 'even' variable for the next iteration
            even = even - 10;

            // Print a vertical bar and move to the next line
            cout << "|" << endl << LEFT << endl;
        }
        // If the row is even
        else    //even rows 
        {
            //Print a vertical bar for even rows
            cout << "| ";

            //Loop through 10 elements and print corresponding values from the 'board' array
            for (int i = 0; i < 10; i++)
            {
                //Check if 'odd' is within the range of the 'board' array
                if (odd >= 0 && odd <= 9)
                {
                    //Check if it's the last element of the row
                    if (odd == 9)
                    {
                        cout << board[odd] << " ";
                        odd = odd + 1;
                    }
                    //For other elements in the row
                    else
                    {
                        cout << board[odd] << "   ";    //From 1 to 9
                        odd = odd + 1;
                    }
                }
                //Check if it's the last element of the row
                else if (i == 9)
                {
                    cout << board[odd] << " ";
                    odd = odd + 1;
                }
                //For other elements in the row
                else
                {
                    cout << board[odd] << "   ";
                    odd = odd + 1;
                }
            }

            //Adjust the 'odd' variable for the next iteration
            odd = odd - 30;

            //Check if it's not the last row
            if (rows != 10)
                cout << "|" << endl << RIGHT << endl;
            //If it's the last row, print a vertical bar and the bottom of the board
            else
                cout << "|" << endl << BOTTOM << endl;
        }
    }

}
bool validateNumber(double num, string message)    //Checks if input is numeric and between 1.0 and 5.0 inclusive
{
	bool returnType(true);   //Default is true
	if (cin.fail())
	{
        system("clear");
		cout << message;
		//Ensures input stream is clear before trying again
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');    //Ignores the newline characters
		returnType = false;
	}
	return returnType;
}
void createSnakes()
{
    for (int i = 0; i < 8; i++)     //Loop repeats 8 times
    {
        int randomLoc = rand() % boardSize;        //Generates a random number between 0 and 99

        if (randomLoc >= 10 && randomLoc <= 98)        //Makes sure number is in range
        {
            if (board[randomLoc] != "S " && board[randomLoc] != "L ")       //Code executes if the location is not already a ladder or snake
                {
                    board[randomLoc] = "S ";        //This string is assigned to the random board location
                    int randomLength;       //Stores the length of the snake
                    do
                        {  
                        /* Generates a random number 0-9 using discrete_distribution, adds 1 to that number (1-10), and then multiplies it by 10 (10-100)
                        Afterwards, generates a random number 0-9 using rand() and adds 1 to that number (1-10)
                        Calculates the difference of the first random number by the second random number (0-99) */
                        randomLength = ((distribution(gen) + 1) * 10) - ((rand() % 10) + 1);
                        if (randomLength <= 9)
                        randomLength = randomLength + 10;       //If the length is less than or equal to 9, 10 is added to the length. This ensures that the user always slides down a snake that is at least one floor lower
                    } while (randomLoc - randomLength <= 1 || board[randomLoc - randomLength] == "S " || board[randomLoc - randomLength] == "L ");       //Continues generating a random number until the length of the snake does not go below the board size and until the ladder end is not a snake or ladder

                    Map.insert(make_pair(randomLoc, randomLength));     //Creates a key-value pair for the ladder. It stores the location of a particular ladder and its length
                }

            else
                i--;    //Makes the for loop end condition return to what it was at the start of the iteration
        }
        else
            i--;    //Makes the for loop end condition return to what it was at the start of the iteration
    }
}
void createLadders()
{
    for (int i = 0; i < 8; i++)     //Loop repeats 8 times
    {
        int randomLoc = rand() % boardSize;        //Generates a random number between 0 and 99. This is the location of the ladder

        if (randomLoc >= 1 && randomLoc <= 89)        //Makes sure number is in range
        {
            if (board[randomLoc] != "S " && board[randomLoc] != "L ")       //Code executes if the location is not already a ladder or snake
                {
                    board[randomLoc] = "L ";        //This string is assigned to the random board location
                    int randomLength;       //Stores the length of the ladder
                    do
                        {  
                        /* Generates a random number 0-9 using discrete_distribution, adds 1 to that number (1-10), and then multiplies it by 10 (10-100)
                        Afterwards, generates a random number 0-9 using rand() and adds 1 to that number (1-10)
                        Calculates the difference of the first random number by the second random number (0-99) */
                        randomLength = ((distribution(gen) + 1) * 10) - ((rand() % 10) + 1);
                        if (randomLength <= 9)
                        randomLength = randomLength + 10;       //If the length is less than or equal to 9, 10 is added to the length. This ensures that the user always climbs a ladder that is at least one floor higher
                    } while (randomLoc + randomLength >= boardSize || board[randomLoc + randomLength] == "S " || board[randomLoc + randomLength] == "L ");       //Continues generating a random number until the length of the ladder does not exceed the board size and until the ladder end is not a snake or ladder

                    Map.insert(make_pair(randomLoc, randomLength));     //Creates a key-value pair for the ladder. It stores the location of a particular ladder and its length
                } 
            else
                i--;    //Makes the for loop end condition return to what it was at the start of the iteration
        }
        else
            i--;    //Makes the for loop end condition return to what it was at the start of the iteration
    }
}
int rollDice()
{
    roll = rand() % 6 + 1;
    return roll;
}
void movePlayer1(string player1, string player2, char& wasSnakeOrLadder, int& ladderLength, int& snakeLength, int& newLocation)
{
    cout << player1 << ", press r to roll the dice: ";
    string r;
    getline(cin, r);           
    while (r != "r" && r != "R")
    {
        system("clear");
        displayBoard();
        displayLengths();       //Displays messages containing the lengths of snakes and ladders
        cout << "You should enter r! ";
        cout << player1 << ", press r to roll the dice: ";
        getline(cin, r);
    }

    rollDice();

    if (p1 == p2)
    {
        board[p2 - 1] = player2.substr(0, 1) + " ";     // leave p2 as it is, but move p1
    }
    else
    {
        if (p1 - 1 < 9)
            board[p1 - 1] = to_string(p1) + " "; // return the previous value to the original number instead of the player name
        else
            board[p1 - 1] = to_string(p1); // return the previous value to the original number instead of the player name
    }
    
    p1 = roll + p1;   // increase the value to move to the next turn 

    if (moveToLadder(p1, player1, ladderLength, newLocation) == 'l')
        wasSnakeOrLadder = 'l';
    else if (moveToSnake(p1, player1, snakeLength, newLocation) == 's')
        wasSnakeOrLadder = 's';

    // if two players meet at the same point
    if (p1 == p2)
    {
         board[p2 - 1] = player1.substr(0, 1) + player2.substr(0, 1);     // leave p2 as it is, but move p1
    }
    else
    {
        board[p1 - 1] = player1.substr(0, 1) + " ";     // insert the name of the player to the right place 
    }
    system("clear");
    displayBoard();     // show the board after the name inserted
    displayLengths();       //Displays messages containing the lengths of snakes and ladders
}
void movePlayer2(string player1, string player2, char& wasSnakeOrLadder, int& ladderLength, int& snakeLength, int& newLocation)
{
    string r;

    // Clear the screen and display the board first
    system("clear");
    displayBoard();
    displayLengths(); // Displays messages containing the lengths of snakes and ladders

    // Print Player 1's move result at the bottom
    if (wasSnakeOrLadder == 's') // If player 1 was on a snake
    {
        cout << player1 << " slid down " << snakeLength + 1 << " spaces and is now at location " << newLocation << ". ";
    }
    else if (wasSnakeOrLadder == 'l') // If player 1 was on a ladder
    {
        cout << player1 << " climbed up " << ladderLength - 1 << " spaces and is now at location " << newLocation << ". ";
    }
    else // If player 1 was not on a snake or ladder
    {
        if (roll == 1)
            cout << player1 << " rolled " << roll << " space and is now at location " << p1 << ". ";
        else
            cout << player1 << " rolled " << roll << " spaces and is now at location " << p1 << ". ";
    }

    wasSnakeOrLadder = 'n'; // Reset to not affect future code

    switch (menu1)
    {
        case 1: // Bot
            cout << "Now, bot will play...";
            cout << endl; // Add a newline for clarity
            this_thread::sleep_for(chrono::seconds(0)); // Pause for 0 seconds after the message
            break;
        case 2: // Friend
            cout << player2 << ", press r to roll the dice: ";
            getline(cin, r);
            while (r != "r" && r != "R")
            {
                system("clear");
                displayBoard();
                displayLengths(); // Displays messages containing the lengths of snakes and ladders
                cout << "You should enter r! ";
                cout << player2 << ", press r to roll the dice: ";
                getline(cin, r);
            }
            break;
        default:
            break;
    }

    rollDice();

    if (p2 == p1)
    {
        board[p1 - 1] = player1.substr(0, 1) + " "; // Insert the name of the player to the right place
    }
    else
    {
        if (p2 - 1 < 9)
            board[p2 - 1] = to_string(p2) + " "; // Return the previous value to the original number
        else
            board[p2 - 1] = to_string(p2); // Return the previous value to the original number
    }

    p2 = roll + p2; // Increase the value to move to the next turn

    if (moveToLadder(p2, player2, ladderLength, newLocation) == 'l')
        wasSnakeOrLadder = 'l';
    else if (moveToSnake(p2, player2, snakeLength, newLocation) == 's')
        wasSnakeOrLadder = 's';

    // If two players meet at the same point
    if (p2 == p1)
    {
        board[p2 - 1] = player1.substr(0, 1) + player2.substr(0, 1); // Leave p2 as it is, but move p1
    }
    else
    {
        board[p2 - 1] = player2.substr(0, 1) + " "; // Insert the name of the player to the right place
    }

    // Clear the screen and display the updated board
    system("clear");
    displayBoard();
    displayLengths(); // Displays messages containing the lengths of snakes and ladders

    if (p2 < boardSize)
    {
        if (wasSnakeOrLadder == 's') // If player 2 was on a snake
        {
            cout << player2 << " slid down " << snakeLength + 1 << " spaces and is now at location " << newLocation << ". ";
        }
        else if (wasSnakeOrLadder == 'l') // If player 2 was on a ladder
        {
            cout << player2 << " climbed up " << ladderLength - 1 << " spaces and is now at location " << newLocation << ". ";
        }
        else // If player 2 was not on a snake or ladder
        {
            if (roll == 1)
                cout << player2 << " rolled " << roll << " space and is now at location " << p2 << ". ";
            else
                cout << player2 << " rolled " << roll << " spaces and is now at location " << p2 << ". ";
        }
    }
    wasSnakeOrLadder = 'n'; // Reset to not affect future code
}
char moveToLadder(int& p0, string player0, int& ladderLength, int& newLocation)
{
    int playerLocation = p0 - 1;        //The location of the ladder that the player landed on
    if (board[playerLocation] == "L ")      //If the player is on the ladder
    {
        board[playerLocation] = player0.substr(0, 1) + "+";     //Updates the board spot with + and the first letter of the player's name 
        system("clear");      //Clears the screen
        displayBoard();     //Displays the updated board
        displayLengths();       //Displays messages containing the lengths of snakes and ladders

        if (roll == 1)
            cout << player0 << " rolled " << roll << " space and landed on a ladder. Press L to climb the ladder: ";        //Sentence adjusted for grammar 
        else
            cout << player0 << " rolled " << roll << " spaces and landed on a ladder. Press L to climb the ladder: ";        //Sentence adjusted for grammar 

        string l;       //Stores the input of the user when he lands on a ladder
        getline(cin, l);        //Requests the user for input
        while (l != "l" && l != "L")        //Loop repeats until user enters l or L
        {
            system("clear");      //Clears the screen
            displayBoard();     //Displays the updated board
            displayLengths();       //Displays messages containing the lengths of snakes and ladders
            cout << "You should enter L! ";     //Error message
            cout << player0 << ", press L to climb the ladder: ";       //Prompts the user to press l
            getline(cin, l);
        }

        ladderLength = Map.at(playerLocation);        //Retrieves the length of the ladder from the map
        newLocation = playerLocation + ladderLength;      //The new location that the player will be on after sliding down the snake
        p0 = newLocation;       //Player moves to the new location
        board[newLocation - 1] = player0.substr(0, 1) + " ";     //Player climbs up the ladder and the ladder end spot changes to the first letter of the player's name
        board[playerLocation] = "L ";   //Move ladder start spot back to "L " after climbing up

        string ladderMessage = "Ladder " + to_string(playerLocation + 1) + " = +" + to_string(ladderLength - 1);        //Stores a message containing the location and length of a ladder
        
        //Checks if the string is in the vector
        auto it = find(laddersVector.begin(), laddersVector.end(), ladderMessage);
        if (it == laddersVector.end())
        {
            laddersVector.push_back(ladderMessage);        //Puts message into vector
        } 

        system("clear");      //Clears the screen
        displayBoard();     //Displays the updated board

        return 'l';    //l is returned if the player was on a ladder
    }
    else
        return 'n';    //n is returned if the player was not a ladder
}
char moveToSnake(int& p0, string player0, int& snakeLength, int& newLocation)
{
    int playerLocation = p0 - 1;        //The location of the snake that the player landed on
    if (board[playerLocation] == "S ")      //If the player is on the snake
    {
        board[playerLocation] = player0.substr(0, 1) + "-";          //Updates the appearance of the board spot with - and the first letter of the player's name 
        system("clear");      //Clears the screen
        displayBoard();     //Displays the updated board
        displayLengths();       //Displays messages containing the lengths of snakes and ladders

        if (roll == 1)
            cout << player0 << " rolled " << roll << " space and landed on a snake. Press S to slide down the snake: ";        //Sentence adjusted for grammar 
        else
            cout << player0 << " rolled " << roll << " spaces and landed on a snake. Press S to slide down the snake: ";        //Sentence adjusted for grammar 

        string s;       //Stores the input of the user when he lands on a snake
        getline(cin, s);        //Requests the user for input
        while (s != "s" && s != "S")        //Loop repeats until user enters s or S
        {
            system("clear");      //Clears the screen
            displayBoard();     //Displays the updated board
            displayLengths();       //Displays messages containing the lengths of snakes and ladders
            cout << "You should enter S! ";     //Error message
            cout << player0 << ", press S to slide down the snake: ";       //Prompts the user to press s
            getline(cin, s);
        }

        snakeLength = Map.at(playerLocation);        //Retrieves the length of the snake from the map
        newLocation = playerLocation - snakeLength;      //The new location that the player will be on after sliding down the snake
        p0 = newLocation;       //Player moves to the new location
        board[newLocation - 1] = player0.substr(0, 1) + " ";     //Player slides down the snake and the snake end spot changes to the first letter of the player's name
        board[playerLocation] = "S ";   //Move snake start spot back to "S " after sliding down

        string snakeMessage = "Snake " + to_string(playerLocation + 1) + " = -" + to_string(snakeLength + 1);        //Stores a message containing the location and length of a snake
        
        //Checks if the string is in the vector
        auto it = find(snakesVector.begin(), snakesVector.end(), snakeMessage);
        if (it == snakesVector.end())
        {
            snakesVector.push_back(snakeMessage);        //Puts message into vector
        } 

        system("clear");      //Clears the screen
        displayBoard();     //Displays the updated board
        
        return 's';    //s is returned if the player was on a snake
    }
    else
        return 'n';    //n is returned if the player was not a snake
}
void play()
{
    string player1, player2;
    string dp1, dp2;
    char wasSorL;
    int ladLength, snakeLen, newLoc;
    switch (menu1)
    {
    case 1: 
        system("clear");
        cout << "\n\n\tEnter your name: ";
        cin >> player1;
        system("clear");
        player2 = "Bot";
        dp1 = player1; // Set dp1 to player1's name
        dp2 = player2; // Set dp2 to "Bot"
        break;
    case 2:
        system("clear");
        displayMenu3(player1, player2);
        system("clear");
        dp1 = player1; // Set dp1 to player1's name
        dp2 = player2; // Set dp2 to player2's name
        break;
    default: 
        break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores the newline characters

    board[0] = player1.substr(0, 1) + player2.substr(0, 1); // The starting position of player 1 and player 2

    displayBoard();
    while (true)
    {
        movePlayer1(player1, player2, wasSorL, ladLength, snakeLen, newLoc);
        if (p1 >= boardSize)
        {
            system("clear");
            board[99] = player1.substr(0, 1) + "  ";
            displayBoard();
            cout << dp1 << " beat " << dp2 << "!\n"; // Use dp1 and dp2 for the victory message
            break;
        }
        movePlayer2(player1, player2, wasSorL, ladLength, snakeLen, newLoc);
        if (p2 >= boardSize)
        {
            system("clear");
            board[99] = player2.substr(0, 1) + "  ";
            displayBoard();
            cout << dp2 << " beat " << dp1 << "!\n"; // Use dp2 and dp1 for the victory message
            break;
        }
    }
}
void displayLengths()
{
    if (snakesVector.size() > 0)
    {
        for (int i = 0; i < snakesVector.size(); i++)
        {
            cout << snakesVector[i] << endl;
        }
        cout << endl;
    }
    if (laddersVector.size() > 0)
    {
        for (int i = 0; i < laddersVector.size(); i++)
        {
            cout << laddersVector[i] << endl;
        }
        cout << endl;
    }
}