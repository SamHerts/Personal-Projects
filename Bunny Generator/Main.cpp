#include <iostream>
#include <conio.h>
#include "Bunny.h"
#include "Colony.h"

using namespace std;

void Pause();


int main(){
	int genCount = 0;
	Colony myColony;
	while (myColony.Continue()){
		myColony.killOld();		
		myColony.Cull();
		myColony.giveBirth();
		myColony.convertMutants();
		myColony.growOld();
		myColony.listColony();
		cout << "Generation: " << genCount << endl;
		genCount++;
		Pause();
	}


	Pause();	
	return 0;

}

void Pause(){

	cout << endl << "Press any key..." << endl;
	_getch();

}
