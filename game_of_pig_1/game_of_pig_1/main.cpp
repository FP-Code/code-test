// Game of Pig Prototype
// Copyright: In the Future

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

// Functions for Versus Mode
int VersusStart();
void PlayVersusGame(int player);
void VersusRoll(int player);
void VersusBank(int player);

// Functions for Bot Mode
int BotStart();
void PlayBotGame(int humanOrBot);
void BotRoll();
void BotBank();
void ComputerTurn();

// Functionality of Game
void Winner(int player);
void DisplayInfo(int versusOrBot);
int RollDie();

// Initialized Global Variables
bool rollAgain = false;
const int k_winningScore = 100;
int roll = 0;
int currentScore = 0;
int playerOneScore = 0, playerTwoScore = 0, computerScore = 0;

int main()
{
    // Casting with an unsigned integer to avoid potential loss of data (according to error message)
    // Keeps the integer for time() at 32 bits
    srand((unsigned int)time(NULL));
    
    // Decision between Versus or Single Player
    int menuChoice = 0;
    
    // Introduction text / Display Rules
    cout << "*** Welcome to the Game of Pig! ***" << endl;
    
    cout << "\nTHE RULES OF PIG" << endl;
    cout << "A two-player dice game where the goal is to be the first to score 100 points\n"
    "-- If the player rolls a 1, their turn ends and they get 0 points for that turn\n"
    "-- If the player rolls a 2-6, that number is added to their turn total,\n"
    "   and they roll again\n"
    "-- Player continues to roll as long as it's their turn\n"
    "-- Player can choose to BANK during their turn, which adds their turn total\n"
    "   to their overall score and ends the turn\n"
    "-- First of the players to reach 100 points wins the game" << endl;
    
    cout << "\nPlease select one of the following options: \n"
    "1. Versus Mode \n"
    "2. Single Player Bot Battle " << endl;
    cout << "You choose: ";
    cin >> menuChoice;
    
    if (menuChoice == 1) // 1 Player Game vs. Bot
    {
        cout << "You have chosen Two Player Versus Mode\n" << endl;
        PlayVersusGame(VersusStart());
        
    }
    else if (menuChoice == 2) // 2 Player Game
    {
        cout << "You have chosen Single Player Bot Battle\n" << endl;
        PlayBotGame(BotStart());
    }
    else
    {
        cout << "You have entered an invalid input." << endl;
    }
    
    return 0;
}

// Initial start of Two Player game
// Chooses which player goes first
int VersusStart()
{
    cout << "Randomly choosing which player goes first..." << endl;
    int player = rand() % 2 + 1;
    if (player == 1)	// Player 1 is chosen
    {
        cout << "Player 1 goes first!" << endl;
        return 1;
    }
    else				// Player 2 is chosen
    {
        cout << "Player 2 goes first!" << endl;
        return 2;
    }
}

// The actual functionality of a Two Player game
void PlayVersusGame(int player)
{
    char input = '0'; // Variable to determine if user Rolls or Banks
    
    if (playerOneScore < k_winningScore && playerTwoScore < k_winningScore) // Conditions to loop in VS game
    {
        if (player == 1)
        {
            cout << "Player 1's Turn!" << endl;
        }
        else
        {
            cout << "Player 2's Turn!" << endl;
        }
        
        do		// Runs once every time it's a player's turn
        {
            // Outputting Roll/Bank choices
            cout << "\"r\" to Roll" << endl;
            cout << "\"b\" to Bank" << endl;
            cout << "Your choice: ";
            cin >> input;
            cout << endl;
            
            // The input to Roll or Bank for both players
            if (input == 'r')
            {
                VersusRoll(player);
            }
            else if (input == 'b')
            {
                VersusBank(player);
            }
            else
            {
                cout << "Invalid input!" << endl;
                rollAgain = false;
            }
        } while (rollAgain); // Determines if a player's turn continues
    }
    // Win conditions for the conclusion of the game
    else
    {
        if (playerOneScore >= k_winningScore)
        {
            Winner(1);
        }
        else
        {
            Winner(2);
        }
    }
}

// Player rolls and continues their turn
void VersusRoll(int player)
{
    roll = RollDie();
    cout << "Player " << player << " rolls the die and gets: " << roll << " points!" << endl;
    if (roll < 7 && roll > 1)		// Die rolls 2-6
    {
        currentScore += roll;
        cout << "Player " << player << "'s current score: " << currentScore << endl;
        rollAgain = true;
    }
    else							// Die rolls a 1
    {
        cout << "Your turn ends and you get 0 points" << endl;
        currentScore = 0;			// Prevents any points to be added to player's total score
        DisplayInfo(1);				// Shows both overall scores at the end of turn
        rollAgain = false;
        if (player == 1)
        {
            PlayVersusGame(2);			// Switch to Player 2
        }
        else
        {
            PlayVersusGame(1);			// Switch to Player 1
        }
    }
}

// When player banks to end their turn
// Note: Player must choose to bank after going over 100 to win game
void VersusBank(int player)
{
    if (player == 1)
    {
        cout << "Player " << player << " chooses to bank." << endl;
        cout << "Turn ends with " << currentScore << " points!" << endl;
        playerOneScore += currentScore;		// Adds the turn's collective score to Player 1 overall score
        DisplayInfo(1);						// Shows both overall scores at the end of turn
        rollAgain = false;
        currentScore = 0;					// Resets the turn's score for the next player
        PlayVersusGame(2);					// Switch to Player 2
    }
    else
    {
        cout << "Player " << player << " chooses to bank." << endl;
        cout << "Turn ends with " << currentScore << " points!" << endl;
        playerTwoScore += currentScore;		// Adds the turn's collective score to Player 2 overall score
        DisplayInfo(1);						// Shows both overall scores at the end of turn
        rollAgain = false;
        currentScore = 0;					// Resets the turn's score for the next player
        PlayVersusGame(1);					// Switch to Player 1
    }
}

//Initial start of the Single Player vs. Bot Game
// Chooses who goes first
int BotStart()
{
    cout << "Randomly choosing if Computer or Player goes first..." << endl;
    int player = rand() % 2 + 1;
    if (player == 1)	// Human Player is chosen
    {
        cout << "Puny Human goes first!" << endl;
        return 1;
    }
    else				// Computer Bot is chosen
    {
        cout << "Mighty Computer goes first!" << endl;
        return 2;
    }
}

// Functionality of Single Player Bot Battle
void PlayBotGame(int humanOrBot)
{
    char input = '0'; // Variable for Human Player to decide to Roll or Bank
    
    if (playerOneScore < k_winningScore && computerScore < k_winningScore) // Conditions to loop in Bot Game
    {
        if (humanOrBot == 1)
        {
            cout << "Puny Human Turn!" << endl;
            do		// Runs once every time it's human player's turn
            {
                // Outputting Roll/Bank choices
                cout << "\"r\" to Roll" << endl;
                cout << "\"b\" to Bank" << endl;
                cout << "Your choice: ";
                cin >> input;
                cout << endl;
                
                // The input to Roll or Bank for player
                if (input == 'r')
                {
                    BotRoll();
                }
                else if (input == 'b')
                {
                    BotBank();
                }
                else
                {
                    cout << "Invalid input!" << endl;
                    rollAgain = false;
                }
            } while (rollAgain); // Determines if player's turn continues
        }
        else
        {
            cout << "Mighty Computer Turn!" << endl;
            do
            {
                ComputerTurn();
            } while (rollAgain);
        }
    }
    // Win conditions for the conclusion of the game
    else
    {
        if (playerOneScore >= k_winningScore)
        {
            Winner(3);			// Displays winning info for player
        }
        else
        {
            Winner(4);			// Displays winning info for computer
        }
    }
}

// Player chooses to Roll in Bot Game
void BotRoll()
{
    roll = RollDie();
    cout << "Puny Human rolls the die and gets: " << roll << " points!" << endl;
    if (roll < 7 && roll > 1)		// Die rolls 2-6
    {
        currentScore += roll;
        playerTwoScore += currentScore;
        cout << "Puny Human's current score: " << currentScore << endl;
        rollAgain = true;
    }
    else							// Die rolls a 1
    {
        cout << "Your turn ends and you get 0 points" << endl;
        currentScore = 0;			// Prevents any points to be added to player's total score
        DisplayInfo(2);				// Shows both Human and Bot overall scores at the end of turn
        rollAgain = false;
        PlayBotGame(2);				// Switch to Bot
    }
}

// Player chooses to Bank in Bot Game
void BotBank()
{
    cout << "Puny Human chooses to bank." << endl;
    cout << "Turn ends with " << currentScore << " points!" << endl;
    playerOneScore += currentScore;		// Adds the turn's collective score to player's overall score
    DisplayInfo(2);						// Shows Human and Bot overall scores at the end of turn
    rollAgain = false;
    currentScore = 0;					// Resets the turn's score for the computer
    PlayBotGame(2);						// Switch to Bot
}

void ComputerTurn()
{
    roll = RollDie();
    
    cout << "Mighty Computer rolls the die and gets: " << roll << " points!" << endl;
    if (roll < 7 && roll > 1)		// Die rolls 2-6
    {
        currentScore += roll;		// Current score increased needed above condition
        if (currentScore < 12)		// Computer rolls again if it has less than 12 points in current score
        {
            cout << "Mighty Computer's current score: " << currentScore << endl;
            rollAgain = true;
        }
        else						// Computer chooses to bank it current score is 12 or higher
        {
            cout << "Mighty Computer chooses to bank." << endl;
            cout << "Turn ends with " << currentScore << " points!" << endl;
            computerScore += currentScore;		// Adds the turn's collective score to computer's overall score
            DisplayInfo(2);						// Shows both Human and Bot overall scores at the end of turn
            rollAgain = false;
            currentScore = 0;					// Resets the turn's score for the next player
            PlayBotGame(1);						// Switch to Player
        }
    }
    else							// Die rolls a 1
    {
        
        cout << "Sad Computer's turn ends and you get 0 points" << endl;
        currentScore = 0;			// Prevents any points to be added to computer's total score
        DisplayInfo(2);				// Shows both Human and Bot overall scores at the end of turn
        rollAgain = false;
        PlayBotGame(1);				// Switch to Player
    }
}

// When the win condition is met this displays
void Winner(int player)
{
    // Versus Mode
    if (player == 1 || player == 2)
    {
        cout << "Player " << player << " wins!" << endl;
        cout << "Final Score: " << endl;
        DisplayInfo(1);
    }
    // Single Player Bot Battle
    else if (player == 3)		// Player wins
    {
        cout << "Puny Human Player wins this time! Lucky!" << endl;
        cout << "Final Score: " << endl;
        DisplayInfo(2);
    }
    else						// Computer wins
    {
        cout << "Mighty Computer crushes Human!" << endl;
        cout << "Final Score: " << endl;
        DisplayInfo(2);
    }
    cout << "GAME OVER!" << endl;
    cout << "Thanks for playing!" << endl;
    cout << endl;
}

// Displays the basic info of the game at each turn.
void DisplayInfo(int versusOrBot)
{
    // If it's a Two Player Versus Game
    if (versusOrBot == 1)
    {
        cout << "Total Amount for Player 1: " << playerOneScore << "." << endl;
        cout << "Total Amount for Player 2: " << playerTwoScore << "." << endl;
        cout << endl;
    }
    // If it's a Single Player Bot Game
    else 
    {
        cout << "Total Amount for Puny Human: " << playerOneScore << "." << endl;
        cout << "Total Amount Mighty Computer: " << computerScore << "." << endl;
        cout << endl;
    }
}

// Random dice roll from 1 to 6
int RollDie()
{
    return rand() % 6 + 1;
}
