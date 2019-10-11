#include "Bunny.h"
#include <string>
using namespace std;



Bunny::Bunny(std::string nameT, std::string colorT, bool isFemaleT, bool isMutantT, Bunny* TparentPTR)
{
	age = 0;
	name = nameT;
	color = colorT;
	isFemale = isFemaleT;
	isMutant = isMutantT;
	parentPTR = TparentPTR;
}
string Bunny::getName(){ return name; }

string Bunny::getColor(){ return color; }

int Bunny::getAge(){ return age; }

bool Bunny::getFemale(){ return isFemale; }

bool Bunny::getMutant(){ return isMutant; }

Bunny* Bunny::getParent(){ return parentPTR; }

void Bunny::setMutant(){ isMutant = true; }

void Bunny::setAge(int ageT){ age = ageT; }
