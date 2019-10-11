#pragma once
#include <string>

static const int MAX_NAMES = 10;
static const int MAX_COLORS = 4;
static const int MAX_AGE = 15;
static const int MAX_MUTANT_AGE = 50;
static const int MAX_COLONY_SIZE = 250;
static const int BORN_MUTANT_PERCENT_CHANCE = 4;
static const int START_SIZE = 8;
static const int CULL_PERCENT = 70;


static const int ADULT_AGE = 3;

static std::string Name[MAX_NAMES] =
{
	"Bob",
	"Nick",
	"Roger",
	"Tim",
	"Ivan",
	"John",
	"Jack",
	"Vincent",
	"Dave",
	"Donald"
};

static std::string colorList[MAX_COLORS] =
{
	"White",
	"Brown",
	"Black",
	"Spotted"
};
