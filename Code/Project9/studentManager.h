#pragma once
#ifndef STUDENT_MANAGER
#define STUDENT_MANAGER
#include "iostream"
#include "vector"
#include "string"
#include "algorithm"

using namespace std;

class student {
public:
	string name;
	int num = 0;
	int mark = 0;
};

int startManager();

#endif