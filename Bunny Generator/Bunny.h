#pragma once
#include <string>

class Bunny
{
	friend class Colony;
public:
	Bunny(std::string, std::string, bool, bool, Bunny*);	

	std::string getName();
	std::string getColor();
	int getAge();
	bool getFemale();
	bool getMutant();
	Bunny* getParent();

	void setMutant();
	void setAge(int);

private:
	std::string name;
	std::string color;
	int age;
	bool isFemale;
	bool isMutant;
	Bunny* parentPTR;
};
