#pragma once
#include <vector>
#include "Global.h"
#include "Bunny.h"


class Colony
{
	friend class Bunny;
public:
	Colony();	
	Bunny* addBunny(Bunny*);
	void killOld();
	void listColony();
	void Cull();
	void giveBirth();
	void convertMutants();
	void growOld();
	bool Continue();

	

private:
	int TOTAL_OLD = 0;
	int TOTAL_CROWD = 0;
	int TOTAL_BORN = 0;
	std::vector<Bunny*> colony;
};
