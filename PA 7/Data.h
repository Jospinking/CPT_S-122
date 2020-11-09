#pragma once
#include <string>
#include "Stack.h"

using namespace std;

class Data
{
public:
	Data(int record_number, long id, string first_name, string last_name,
		string email, string units, string program, string level
	) : record_number(record_number), id(id), first_name(first_name)
		, last_name(last_name), email(email), units(units), program(program),
		level(level), absences(0)
	{}
	Data() {}
	int record_number;
	long id;
	string first_name;
	string last_name;
	string email;
	string units;
	string program;
	string level;

	int absences;
	Stack absence_dates;
};