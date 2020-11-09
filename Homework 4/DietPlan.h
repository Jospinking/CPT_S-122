#pragma once
#include <string>
#include <iostream>
using namespace std;
class DietPlan {
private:
	// instance members for the Diet Plan type
	int goal;
	string name;
	string date;

public:
	// default constructor
	DietPlan();
	// Overloaded constructor
	DietPlan(int goal, string name, string date);

	// Copy constructor, that other object will be copied to this object
	DietPlan(const DietPlan &other);

	// Destructor
	~DietPlan();

	// getters or accessors
	int getGoal() const;
	string getName() const;
	string getDate() const;

	// helper methods
	void editGoal();

	// friend function declaration

	// the DietPlan reference is const, because we are not suppose to change the content
	// of diet plan object in this function, this function will only take the content
	// of the diet plan and will push that into the << 
	friend ostream& operator<< (ostream& out, const DietPlan& dietPlan);

	// the thing is reverse here, we need to pull out the content from >> and 
	// then we need to assign them into the dietPlan object, so dietPlan object reference 
	// will needed to be updated here, that is why here it is not constant
	friend istream& operator >> (istream& in, DietPlan& dietPlan);

};




