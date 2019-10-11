#include "Colony.h"
#include <time.h>
#include <iostream>
#include <algorithm>

using namespace std;
bool pred(Bunny*);
bool pred2(Bunny*);
int oldDead = 0;
int cullDead = 0;
int newCount = 0;


Colony::Colony()
{
	srand(time(NULL));	
	for (int i = 0; i < START_SIZE; i++){
		addBunny(NULL);
	}
}


Bunny* Colony::addBunny(Bunny* motherPTR){
	Bunny* newBunnyPTR =new Bunny(Name[rand() % MAX_NAMES], colorList[rand() % MAX_COLORS], rand() % 2, (rand() % 100+1)< BORN_MUTANT_PERCENT_CHANCE, motherPTR);
	colony.push_back(newBunnyPTR);	
	//cout << "address " << newBunnyPTR << endl;
	return newBunnyPTR;

}

void Colony::killOld(){
	colony.erase(remove_if(colony.begin(), colony.end(), pred2), colony.end());
}
	bool pred2(Bunny* temp){
		bool flag;
		flag = temp->getMutant() ? (temp->getAge() > MAX_MUTANT_AGE) : (temp->getAge() > MAX_AGE);
		if (flag == true){
			oldDead++;
		}
		return flag;
}

void Colony::listColony(){
	int mutantCount = 0;
	int maleCount = 0;
	int femaleCount = 0;
	for (Bunny* i : colony){
		if (i->getMutant()){
			mutantCount++;
		}
		else{
			if (i->getFemale()){
				femaleCount++;
			}
			else{
				maleCount++;
			}
		}
		
		cout << (*i).getName() << " " << i->getColor() << " " << i->getAge() << " " << (i->getFemale() ? "Female" : "Male") << " " << (i->getParent() == NULL ? "God" : i->getParent()->getName()) << " "<< (i->getMutant()?"MUTANT":"Normal") << endl;
	}
	cout << endl;
	cout << "There are " << mutantCount << " mutant bunnies" << endl;
	cout << "There are " << femaleCount << " female bunnies" << endl;
	cout << "There are " << maleCount << " male bunnies" << endl;
	cout << newCount << " bunnies were born." << endl;
	cout << oldDead << " bunnies died of old age." << endl;
	cout << cullDead << " bunnies died from overcrowding." << endl;
	cout << "Colony size: " << colony.size() << endl;
	cout << TOTAL_BORN<< " total bunnies have been born." << endl;
	cout << TOTAL_OLD << " total bunnies have died of old age." << endl;
	cout << TOTAL_CROWD << " total bunnies have died from overcrowding." << endl;
	cout << endl << endl;
	TOTAL_OLD += oldDead;
	TOTAL_CROWD += cullDead;
	TOTAL_BORN += newCount;
	oldDead = 0;
	cullDead = 0;
	newCount = 0;
}

void Colony::Cull(){
	if (colony.size() > MAX_COLONY_SIZE){
		cout << "Colony too big, beginning a cull." << endl;
		colony.erase(remove_if(colony.begin(), colony.end(), pred), colony.end());
	}
	else{
		cout << "There are " << colony.size() << " bunnies" << endl;
	}
}
	bool pred(Bunny* temp){

		bool flag;
		flag = (rand() % 100 + 1 < CULL_PERCENT);
		if (flag == true){
			cullDead++;
		}
		return flag;
}

void Colony::giveBirth(){
	vector<Bunny*> femaleList;
	cout << "Giving Birth" << endl;
	int maleCount = 0;
	for (Bunny* i : colony){
		if (!i->getMutant()){//if not a mutant
			if (i->getFemale() && i->getAge() >= ADULT_AGE){//if female add to list for giving birth
				femaleList.push_back(i);
			}
			else{//if male, count
				maleCount++;
			}
		}		
	}
	for (int p = 0; p < maleCount; p++){
		for (Bunny* j : femaleList){			
			cout << "Bunny " << j->getName() << " gave birth to " << addBunny(j)->getName() <<  endl;			
		}
	}
	





}

void Colony::convertMutants(){
	
	int mutantCount = 0;
	for (Bunny* i : colony){
		if (i->getMutant()){
			mutantCount++;
		}
	}
	if (mutantCount > 0){
		cout << "The mutants are spreading!!!" << endl;
	}
	for (Bunny* i : colony){
		if (!i->getMutant() && mutantCount > 0){
			i->setMutant();
			mutantCount--;
		}
	}
}

void Colony::growOld(){
	for (Bunny* i : colony){
		i->setAge(i->getAge()+1);
	}
}

bool Colony::Continue(){
	int count = 0;
	bool flag = true;
	for (Bunny* i : colony){
		if (i->getMutant()){
			count++;
		}
	}
	if (count == colony.size()){
		flag = false;
	}
	else if (colony.size() == 0){
		flag = false;
	}
	return flag;
}
