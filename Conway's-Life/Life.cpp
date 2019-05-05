#include <iostream>
#include <random>
#include <time.h>
#include <array>
#include <Windows.h>
#include <vector>

using namespace std;

struct OBJ
{
	COORD at;
	char self;
};

const int GRIDSIZE_X{ 40 }; //Length
const int GRIDSIZE_Y{ 20 }; // Height
const int PERCENT = 35; // percent of alive cells to dead cells
const char ALIVE = '#';
const char DEAD = '.';

typedef std::array<std::array<int, GRIDSIZE_Y + 1>, GRIDSIZE_X + 1> Grid; //2D C++ Grid

int checkCell(Grid, COORD); //Returns number of neighbors of cell
void Draw(vector<OBJ>&); // Draws to screen
void ShowConsoleCursor(bool);
void start(Grid&, OBJ&, vector<OBJ>&);

int main() {
	srand(time(NULL));//Seeding
	Grid board, next;//Shown board and updated board
	int neighbors = 0;//Number of alive neighbors of a cell
	OBJ object;
	vector<OBJ> changeMe;
	
	ShowConsoleCursor(false);	
	start(board, object, changeMe);	

	while (true){
		if (GetAsyncKeyState(VK_SPACE))
		{
			start(board, object, changeMe);
		}
		
		Draw(changeMe);//Draw the board
		changeMe.clear();
		for (COORD it = { 0,0 }; it.X < GRIDSIZE_X; it.X++) {// Fill board
			for (it.Y = 0; it.Y < GRIDSIZE_Y; it.Y++) {

				board[it.X][it.Y] ? object.self = ALIVE : object.self = DEAD;
			
				object.at = it;
				neighbors = checkCell(board, it); // check neighbor count
				if (!board[it.X][it.Y] && neighbors == 3) { // if dead and 3 neighbors, come alive
					next[it.X][it.Y] = 1;
					object.self = ALIVE;

				}
				else if (board[it.X][it.Y] && (neighbors < 2 || neighbors > 3)) {// if alive and less than 2 or more than 3 neighbors, die.
					next[it.X][it.Y] = 0;
					object.self = DEAD;
				}
				else {//transfer old board to new board
					next[it.X][it.Y] = board[it.X][it.Y];
				}
				changeMe.push_back(object);
			}
		}		
		board.swap(next);//swap new board back to old board, erasing old board
	}
	return 0;
}

int checkCell(Grid array, COORD myC) {
	int count = 0;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {

			int row = (myC.X + i + GRIDSIZE_X) % GRIDSIZE_X;
			int col = (myC.Y + j + GRIDSIZE_Y) % GRIDSIZE_Y;
			count += array[row][col];
		}
	}
	count -= array[myC.X][myC.Y];
	return count;
}

void Draw(vector<OBJ>& myVec) {
	for (OBJ it : myVec) {
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), it.at);
		cout << it.self;
	}
}
void start(Grid& board, OBJ& object, vector<OBJ>& changeMe) {
	for (COORD it = { 0,0 }; it.X < GRIDSIZE_X; it.X++) {// Fill board
		for (it.Y = 0; it.Y < GRIDSIZE_Y; it.Y++) {
			object.at = it;
			if (1 + rand() % 100 < PERCENT) {
				board[it.X][it.Y] = 1;
				object.self = ALIVE;
			}
			else {
				board[it.X][it.Y] = 0;
				object.self = DEAD;
			}

			changeMe.push_back(object);
		}
	}
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
