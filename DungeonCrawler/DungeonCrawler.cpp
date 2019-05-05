#include <iostream>
#include <time.h>   //Both of these are needed for Code::Blocks to use rand
#include <stdlib.h> //Both of these are needed for Code::Blocks to use rand
#include <windows.h>

//ADD TWO PLAYER WHERE THEY HAVE TO TRAP EACH OTHER - ONE CREATES TRAPS, OTHER ATTEMPTS TO ATTACK THE OTHER PLAYER
//ADD TRAPS AS AN ARRAY (MULTI-DIMENSIONAL) WITH RANDOM GRID LOCATOR - EASIER TO CREATE MULTIPLE TRAPS ESPECIALLY FOR TWO PLAYER *DONE*

#define HEIGHT 10
#define WIDTH 12
#define TRAPS 20 //How many traps? The more traps the longer it takes to load
#define ENEMIES 8 //How many enemies? The more enemies the longer it takes to load

char GameBoard[HEIGHT][WIDTH]; //GameBoard

int i, j; //Global Counters

int action, enemyMove;
bool quit = false;
int posy = 0, posx = 0; //Player pOSition - X-grid/Y-grid
int tosy = (HEIGHT - 1), tosx = (WIDTH - 1); //Treasure pOSition
int TrapLocations[TRAPS][2]; //Trap location array
int EnemyLocations[ENEMIES][2]; //Enemy location array

char player = 'G'; //The Player Character
char board = '.'; //Blank Board
char trap = 'T'; //Trap symbol
char treasure = 'X'; //Treasure symbol
char enemy = 'E'; //Enemy character

using namespace std;

void BlankBoard(char GameBoard[HEIGHT][WIDTH]); //Used once to create a blank board
void PrintBoard(char GameBoard[HEIGHT][WIDTH]); //Prints out the current board
void ActionLoop(char GameBoard[HEIGHT][WIDTH]); //Handles all events around a user's turn
void EnemyMove(char GameBoard[HEIGHT][WIDTH]); //Handles enemy moves
bool AmIDead(char GameBoard[HEIGHT][WIDTH]); //Checks to see if player is dead

int main()
{
	srand((unsigned)time(0));
	cout << "Please wait while the game loads...";

	for (i = 0; i < TRAPS; i++)
	{
		TrapLocations[i][0] = (rand() % (HEIGHT)+1);
		TrapLocations[i][1] = (rand() % (WIDTH)+1);
	}

	for (i = 0; i < ENEMIES; i++)
	{
		EnemyLocations[i][0] = (rand() % (HEIGHT)+1);
		EnemyLocations[i][1] = (rand() % (WIDTH)+1);
	}

	//cout << string(100, '\n');
	cout << "Welcome to Dungeon Crawl!\n";
	cout << "Use the arrows on the number pad followed by enter to move\nNOTE: Make sure NUM LOCK is on!\n";
	cout << "To begin press ENTER\n> ";
	cin.get();

	BlankBoard(GameBoard);
	GameBoard[posy][posx] = player; //Creates the player on the board
	GameBoard[tosy][tosx] = treasure; //Creates the treasure
	for (i = 0; i < TRAPS; i++) //Creating traps
	{
		while (GameBoard[TrapLocations[i][0]][TrapLocations[i][1]] != board)
		{
			TrapLocations[i][0] = (rand() % (HEIGHT)+1);
			TrapLocations[i][1] = (rand() % (WIDTH)+1);
		}
		GameBoard[TrapLocations[i][0]][TrapLocations[i][1]] = trap;
	}
	for (i = 0; i < ENEMIES; i++) //Creating enemies
	{
		while (GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] != board)
		{
			EnemyLocations[i][0] = (rand() % (HEIGHT)+1);
			EnemyLocations[i][1] = (rand() % (WIDTH)+1);
		}
		GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] = enemy;
	}

	while (quit == false)
	{
		//cout << string(20, '\n');
		ActionLoop(GameBoard); //Prints board, goes through steps with user, and goes through enemy moves
	}

	cout << "\nPress ENTER to exit\n";
	cin.get();
	cin.get();
	return 0;
}

void BlankBoard(char GameBoard[HEIGHT][WIDTH])
{
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			GameBoard[i][j] = board;
		}
	}
}

void PrintBoard(char GameBoard[HEIGHT][WIDTH])
{
	system("cls");
	for (i = 0; i < HEIGHT; i++)
	{
		for (j = 0; j < WIDTH; j++)
		{
			cout << GameBoard[i][j];
		}
		cout << endl;
	}
}

void ActionLoop(char GameBoard[HEIGHT][WIDTH])
{
	PrintBoard(GameBoard);
	if (!AmIDead(GameBoard))
	{
		cout << "\n> ";
		cin >> action;
		while (action != 2 && action != 4 && action != 6 && action != 8)
		{
			cout << "Please only use 2, 4, 6, and 8 on your number pad as arrows.\n";
			cout << "Once you choose a number press ENTER to confirm\n> ";
			cin >> action;
		}

		switch (action)
		{
		case 2:
			if (posy == (HEIGHT - 1))
				break;
			else
			{
				GameBoard[posy][posx] = board;
				posy += 1;
				GameBoard[posy][posx] = player;
				break;
			}

		case 4:
			if (posx == 0)
				break;
			else
			{
				GameBoard[posy][posx] = board;
				posx -= 1;
				GameBoard[posy][posx] = player;
				break;
			}

		case 6:
			if (posx == (WIDTH - 1))
				break;
			else
			{
				GameBoard[posy][posx] = board;
				posx += 1;
				GameBoard[posy][posx] = player;
				break;
			}

		case 8:
			if (posy == 0)
				break;
			else
			{
				GameBoard[posy][posx] = board;
				posy -= 1;
				GameBoard[posy][posx] = player;
				break;
			}
		}
		if (posy == tosy && posx == tosx)
		{
			cout << "\nYou win!\a\a\n";
			quit = true;
		}
		EnemyMove(GameBoard); //Enemies move
	}
}

void EnemyMove(char GameBoard[HEIGHT][WIDTH])
{
	srand((unsigned)time(0));

	for (i = 0; i < ENEMIES; i++)
	{
		enemyMove = (rand() % 4 + 1);

		switch (enemyMove)
		{
		case 1:
			if (GameBoard[EnemyLocations[i][0] - 1][EnemyLocations[i][1]] == board || GameBoard[EnemyLocations[i][0] - 1][EnemyLocations[i][1]] == player)
			{
				GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] = board;
				GameBoard[--EnemyLocations[i][0]][EnemyLocations[i][1]] = enemy;
				break;
			}
			else
				break;

		case 2:
			if ((GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1] + 1] == board || GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1] + 1] == player) && EnemyLocations[i][1] + 1 < WIDTH)
			{
				GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] = board;
				GameBoard[EnemyLocations[i][0]][++EnemyLocations[i][1]] = enemy;
				break;
			}
			else
				break;

		case 3:
			if ((GameBoard[EnemyLocations[i][0] + 1][EnemyLocations[i][1]] == board || GameBoard[EnemyLocations[i][0] + 1][EnemyLocations[i][1]] == player) && EnemyLocations[i][0] + 1 < HEIGHT)
			{
				GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] = board;
				GameBoard[++EnemyLocations[i][0]][EnemyLocations[i][1]] = enemy;
				break;
			}
			else
				break;

		case 4:
			if ((GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1] - 1] == board || GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1] - 1] == player) && EnemyLocations[i][1] - 1 > -1)
			{
				GameBoard[EnemyLocations[i][0]][EnemyLocations[i][1]] = board;
				GameBoard[EnemyLocations[i][0]][--EnemyLocations[i][1]] = enemy;
				break;
			}
			else
				break;
		}
	}
}

bool AmIDead(char GameBoard[HEIGHT][WIDTH])
{
	for (i = 0; i < TRAPS; i++)
	{
		if (GameBoard[TrapLocations[i][0]][TrapLocations[i][1]] == player)
		{
			cout << "\nYou lose...\a\n";
			quit = true;
			return true;
		}
	}
	for (i = 0; i < ENEMIES; i++)
	{
		if (EnemyLocations[i][0] == posy && EnemyLocations[i][1] == posx)
		{
			cout << "\nYou lose...\a\n";
			quit = true;
			return true;
		}
	}
	return false;
}
