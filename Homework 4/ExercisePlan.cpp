#include "ExercisePlan.h"

ExercisePlan::ExercisePlan() {
	this->goal = 0;
	this->name = "No Name";
	this->date = "12/31/9999";
}

ExercisePlan::ExercisePlan(int goal, string name, string date) {
	this->goal = goal;
	this->name = name;
	this->date = date;
}

ExercisePlan::ExercisePlan(const ExercisePlan& other) {
	// other object cannot be updated as that is const
	this->goal = other.goal;
	this->name = other.name;
	this->date = other.date;
}

/**
*  Implementation of destructor
*/
ExercisePlan::~ExercisePlan() {
	// Not required, we do not have any kind of dynamic memory inside of this class
	// so nothing to do for clean up
}

// Getters
int ExercisePlan::getGoal() const {
	return this->goal;
}
string ExercisePlan::getName() const {
	return this->name;
}
string ExercisePlan::getDate() const {
	return this->date;
}
void ExercisePlan::editGoal() {
	// first display the content of the current plan
	std::cout << *this << endl;
	// Now ask for the new goal
	std::cout << "Enter the goal: ";
	// read the goal
	std::cin >> this->goal;
}

ostream& operator<< (ostream& out, const ExercisePlan& exercisePlan) {
	out << exercisePlan.getName() << std::endl;
	out << exercisePlan.getGoal() << std::endl;
	out << exercisePlan.getDate() << std::endl;
	// return the out object to the caller that contains the inserted information.
	return out;
}
istream& operator >> (istream& in, ExercisePlan& exercisePlan) {
	in >> exercisePlan.name;
	in >> exercisePlan.goal;
	in >> exercisePlan.date;
	//std::cout << "DEBUG-- " << exercisePlan.name <<", " <<exercisePlan.getGoal() << ", " << exercisePlan.getDate() << std::endl;
	return in;
}