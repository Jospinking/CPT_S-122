// Implementation of all the methods of diet Plan
#include "DietPlan.h"

/**

classname::methodname

*/

/**
* Implementation of default constructor
*/
DietPlan::DietPlan() {
	this->goal = 0;
	this->name = "No Name";
	this->date = "12/31/9999";
}

/**
*  Overloaded constructor
*/
DietPlan::DietPlan(int goal, string name, string date) {

	this->goal = goal;
	this->name = name;
	this->date = date;
}

/**
* Implementation of the copy constructor
*
*/
DietPlan::DietPlan(const DietPlan &other) {
	// other object cannot be updated as that is const
	this->goal = other.goal;
	this->name = other.name;
	this->date = other.date;
}

/**
*  Implementation of destructor
*/
DietPlan::~DietPlan() {
	// Not required, we do not have any kind of dynamic memory inside of this class
	// so nothing to do for clean up
}

// Getters
int DietPlan::getGoal() const {
	return this->goal;
}
string DietPlan::getName() const {
	return this->name;
}
string DietPlan::getDate() const {
	return this->date;
}

void DietPlan::editGoal() {
	// first display the content of the current plan
	std::cout << *this << endl;
	// Now ask for the new goal
	std::cout << "Enter the goal: ";
	// read the goal
	std::cin >> this->goal;

}

ostream& operator<< (ostream& out, const DietPlan& dietPlan) {
	out << dietPlan.getName() << std::endl;
	out << dietPlan.getGoal() << std::endl;
	out << dietPlan.getDate() << std::endl;
	// return the out object to the caller that contains the inserted information.
	return out;
}

istream& operator >> (istream& in, DietPlan& dietPlan) {
	in >> dietPlan.name;
	in >> dietPlan.goal;
	in >> dietPlan.date;
	return in;
}




