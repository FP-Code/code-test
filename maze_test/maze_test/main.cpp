//  Created by Yo' Boy on 3/10/17.
//  Copyright © 2017 And stuff

#include <iostream>
using namespace std;

void PrintMaze();
void WinMessage();

char player = '@';

char maze[5][5] = {
    {'+', '+', '+', '+', '+'},
    {'+', player, ' ', ' ', '+'},
    {'+', ' ', '+', ' ', '+'},
    {'+', ' ', ' ', ' ', '+'},
    {'+', '+', '+', ' ', '+'}
};


int numOfMoves = 0;
bool viewMaze = false;

int main()
{
    
    int posX = 1, posY = 1;

    char input = ' ';
    
    cout << "Behold the Maze of Antiquity and Amazingness!\n" << endl;
    do
    {
        do
        {
            PrintMaze();
            cout << "Type W A S D to navigate" << endl;
            cout << "Your choice: ";
            cin >> input;
        
            if ((input == 'w' || input == 'W') && (maze[posY - 1][posX] == ' ')) // North
            {
                maze[posY][posX] = ' ';
                posY -= 1;
                maze[posY][posX] = player;
                numOfMoves += 1;
            }
            else if ((input == 's' || input == 'S') && (maze[posY + 1][posX] == ' ')) // South
            {
                maze[posY][posX] = ' ';
                posY += 1;
                maze[posY][posX] = player;
                numOfMoves += 1;
            }
            else if ((input == 'a' || input == 'A') && (maze[posY][posX - 1] == ' ')) // West
            {
                maze[posY][posX] = ' ';
                posX -= 1;
                maze[posY][posX] = player;
                numOfMoves += 1;
            }
            else if ((input == 'd' || input == 'D') && (maze[posY][posX + 1] == ' ')) // East
            {
                maze[posY][posX] = ' ';
                posX += 1;
                maze[posY][posX] = player;
                numOfMoves += 1;
            }
            else
            {
                viewMaze = false;
            }

            PrintMaze();
        
        } while (maze[4][3] != player);
        viewMaze = true;
    } while (!viewMaze);
    
    WinMessage();
    return 0;
}

void PrintMaze()
{
    cout << "THE MAZE" << endl;
    
    for (int x = 0; x < 5; ++x)
    {
        
        for (int y = 0; y < 5; ++y)
        {
            cout << maze[x][y];
        }
        cout << endl;
    }
}

void WinMessage()
{
    cout << "You'v reached the end of the Maze in " << numOfMoves << " moves!" << endl;
    cout << "You win!" << endl;
}



