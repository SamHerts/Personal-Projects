#include <iostream>
#include <random>
#include <time.h>
using namespace std;

int main() {
	srand(time(NULL));
	int A = 0, B = 0, C = 0, winCount = 0, playCount = 0, n = 10000;
	bool Switch;
	char select, choose;	

	cout << "Switch? (Y/N) ";	
	cin >> choose;
	(choose == 'Y' || choose == 'y') ? Switch = true : Switch = false;
	for(int i = 0; i < n; i++){
		int p = rand() % 100 + 1;
		if (p < 33) { // randomly choose a door to win
			A = 1;
			B = 0;
			C = 0;
		}
		else if (p > 33 && p < 66) {
			A = 0;
			B = 1;
			C = 0;
		}
		else if (p > 66) {
			A = 0;
			B = 0;
			C = 1;
		}

		//cout << "Choose a door: " << endl;
		//cout << "A   B   C" << endl;
		//cin >> select;
		
		int j = rand() % 100 + 1;
		if (j < 33) { //randomly choose a door for the user to pick
			select = 'A';
		}
		else if (j > 33 && j < 66) {
			select = 'B';
		}
		else if (j > 66) {
			select = 'C';
		}
		//cout << "You chose: " << select << endl;

		int comp = rand() % 100 + 1;
		char show;
		if (A) { //show the user an empty door
			if (select == 'A') {
				comp > 50 ? show = 'B' : show = 'C';
			}
			else if (select == 'B') {
				show = 'C';
			}
			else if (select == 'C') {
				show = 'B';
			}
		}
		if (B) {
			if (select == 'A') {
				show = 'C';
			}
			else if (select == 'B') {
				comp > 50 ? show = 'A' : show = 'C';
			}
			else if (select == 'C') {
				show = 'A';
			}
		}
		if (C) {
			if (select == 'A') {
				show = 'B';
			}
			else if (select == 'B') {
				show = 'A';
			}
			else if (select == 'C') {
				comp > 50 ? show = 'A' : show = 'B';
			}
		}
		//cout << "A guaranteed empty door is: " << show << endl;
		//cout << "Would you like to change your answer now? (Y/N)";
		
		if (Switch) {
			//cout << "Chose to Switch" << endl;
			if (select == 'A') {
				if (show == 'B') {
					select = 'C';
				}
				else if (show == 'C') {
					select = 'B';
				}
			}
			else if (select == 'B') {
				if (show == 'A') {
					select = 'C';
				}
				else if (show == 'C') {
					select = 'A';
				}
			}
			else if (select == 'C') {
				if (show == 'A') {
					select = 'B';
				}
				else if (show == 'B') {
					select = 'A';
				}
			}
		}
		if ((select == 'A' && A == 1) || (select == 'B' && B == 1) || (select == 'C' && C == 1)) {
			winCount++;
			playCount++;
			//cout << "You chose the correct door!" << endl;
		}
		else {
			playCount++;
			//cout << "You chose the wrong door!" << endl;
		}
		//system("CLS");
		
	}
	cout << "Win rate: " << ((float)winCount / (float)playCount) * 100 << '%' << endl;

	std::system("pause");
	return 0;
}
