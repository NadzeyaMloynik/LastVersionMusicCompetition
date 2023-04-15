#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "interface.h"

using namespace std;

struct info {
	string login;
	string password;
	int role;
	bool isActive;
};

struct infCont {
	string name;
	int year;
	string country;
	string musicInst;
	int place;
	double rating;
};

struct ApplyCont {
	string name;
	int year;
	string country;
	string musicInst;
};

extern vector<info> vectInf;
extern vector<infCont> vectCont;
extern vector<ApplyCont> vectApply;