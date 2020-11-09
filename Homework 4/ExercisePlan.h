#pragma once
#include <string>
#include <iostream>
using namespace std;

class ExercisePlan {
private:
	int goal;

	string name;
	string date;

public:
	// Default constructor
	ExercisePlan();

	// Overloaded constructor
	ExercisePlan(int goal, string name, string date);

	// Copy Constructor
	ExercisePlan(const ExercisePlan& other);

	// destructor
	~ExercisePlan();

	// getters or accessors
	int getGoal() const;
	string getName() const;
	string getDate() const;

	// helper function
	void editGoal();

	friend ostream& operator<< (ostream& out, const ExercisePlan& exercisePlan);
	friend istream& operator >> (istream& in, ExercisePlan& exercisePlan);

};