
#include "FitnessAppWrapper.h"
using namespace std;

FitnessAppWrapper::FitnessAppWrapper() {
	// openning the file streams
	file_diet.open("dietPlans.txt", ios::in | ios::out);
	if (!file_diet) {
		std::cout << "Unable to open dietPlans.txt" << endl;
		std::cout << "Make sure that the file exists";
		exit(0);
	}
	file_exercise.open("exercisePlans.txt", ios::in | ios::out);
	if (!file_exercise) {
		std::cout << "Unable to open exercisePlans.txt" << endl;
		std::cout << "Make sure that the file exists";
		exit(0);
	}
	// the input file streams are there    
}

void FitnessAppWrapper::loadDailyDietPlan(fstream &fileStream, DietPlan &plan) {
	fileStream >> plan;
}
void FitnessAppWrapper::loadWeeklyDietPlan(fstream &fileStream, vector <DietPlan>& pWeeklyDietPlans) {
	// we need to move the file object at the beginning of the file 
	// begore we could read from the file
	fileStream.clear();
	fileStream.seekg(0, ios::beg);
	// Now that the file stream has been move to the beginning we can read
	// but first we need to clear the vector
	pWeeklyDietPlans.clear();
	DietPlan dietPlan;
	// trying to read a single record from the file, if that exists then 
	// we will go inside of the loop
	loadDailyDietPlan(fileStream, dietPlan);
	while (fileStream) {
		// Now that we read a diet plan, so push this diet_plan into the vector
		pWeeklyDietPlans.push_back(dietPlan);
		// read next single record from the file and get that in dietPlan object
		loadDailyDietPlan(fileStream, dietPlan);
	}


}
void FitnessAppWrapper::displayDailyDietPlan(const DietPlan& dietPlan) const {
	std::cout << dietPlan;
	std::cout << std::endl;
}
void FitnessAppWrapper::displayWeeklyDietPlan(const vector<DietPlan>& pWeeklyDietPlan) const {
	for (auto it = pWeeklyDietPlan.begin(); it != pWeeklyDietPlan.end(); ++it) {
		displayDailyDietPlan(*it);
	}
}
void FitnessAppWrapper::storeDailyDietPlan(fstream& fileStream, DietPlan& dietPlan) {
	fileStream.clear();
	fileStream.seekg(0, ios::beg);
	fileStream << dietPlan;

}
void FitnessAppWrapper::storeWeeklyDietPlan(fstream& fileStream, vector<DietPlan>& pWeeklyDietPlan) {
	for (auto it = pWeeklyDietPlan.begin(); it != pWeeklyDietPlan.end(); ++it) {
		storeDailyDietPlan(fileStream, *it);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// Exercies starts
void FitnessAppWrapper::loadDailyExercisePlan(fstream &fileStream, ExercisePlan &plan) {
	fileStream >> plan;
}
void FitnessAppWrapper::loadWeeklyExercisePlan(fstream &fileStream, vector <ExercisePlan>& pWeeklyExercisePlans) {
	// we need to move the file object at the beginning of the file 
	// begore we could read from the file
	fileStream.clear();
	fileStream.seekg(0, ios::beg);
	// Now that the file stream has been move to the beginning we can read
	// but first we need to clear the vector
	pWeeklyExercisePlans.clear();
	ExercisePlan exercisePlan;
	// try to read the first record from the file and get that in exercisePlan object
	loadDailyExercisePlan(fileStream, exercisePlan);
	while (fileStream) {
		// Now push this diet_plan into the vector
		pWeeklyExercisePlans.push_back(exercisePlan);
		// read next single record from the file and get that in exercisePlan object
		loadDailyExercisePlan(fileStream, exercisePlan);
	}

}
void FitnessAppWrapper::displayDailyExercisePlan(const ExercisePlan& exercisePlan) const {
	std::cout << exercisePlan;
	std::cout << std::endl;
}
void FitnessAppWrapper::displayWeeklyExercisePlan(const vector<ExercisePlan>& pWeeklyExercisePlan) const {
	for (auto it = pWeeklyExercisePlan.begin(); it != pWeeklyExercisePlan.end(); ++it) {
		displayDailyExercisePlan(*it);
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void FitnessAppWrapper::storeDailyExercisePlan(fstream& fileStream, ExercisePlan& exercisePlan) {
	fileStream.clear();
	fileStream.seekg(0, ios::beg);
	fileStream << exercisePlan;
}
void FitnessAppWrapper::storeWeeklyExercisePlan(fstream& fileStream, vector<ExercisePlan>& pWeeklyExercisePlan) {
	for (auto it = pWeeklyExercisePlan.begin(); it != pWeeklyExercisePlan.end(); ++it) {
		storeDailyExercisePlan(fileStream, *it);
	}
}

void FitnessAppWrapper::runApp(void) {
	bool quit = false;
	while (!quit) {
		displayMenu();
		cout << "Please input your option: ";
		int option;
		cin >> option;

		switch (option) {
		case 1: loadWeeklyDietPlan(file_diet, weeklyDietPlans);
			break;
		case 2: loadWeeklyExercisePlan(file_exercise, weeklyExercisePlans);
			break;
		case 3: storeWeeklyDietPlan(file_diet, weeklyDietPlans);
			break;
		case 4: storeWeeklyExercisePlan(file_exercise, weeklyExercisePlans);
			break;
		case 5:displayWeeklyDietPlan(weeklyDietPlans);
			break;
		case 6:displayWeeklyExercisePlan(weeklyExercisePlans);
			break;
		case 7:
			editDailyDietPlan(weeklyDietPlans);
			break;
		case 8:
			editDailyExercisePlan(weeklyExercisePlans);
			break;
		case 9: quit = true;
			// storeWeeklyDietPlan(file_diet, weeklyDietPlans);
			// storeWeeklyExercisePlan(file_exercise, weeklyExercisePlans);
			break;
		}



	}

}

void FitnessAppWrapper::displayMenu() {
	std::cout << "1.    Load weekly diet plan from file. " << std::endl;
	std::cout << "2.    Load weekly exercise plan from file." << std::endl;
	std::cout << "3.    Store weekly diet plan to file." << std::endl;
	std::cout << "4.    Store weekly exercise plan to file." << std::endl;
	std::cout << "5.    Display weekly diet plan to screen." << std::endl;
	std::cout << "6.    Display weekly exercise plan to screen." << std::endl;
	std::cout << "7.    Edit daily diet plan." << std::endl;
	std::cout << "8.    Edit daily exercise plan." << std::endl;
	std::cout << "9.    Exit." << std::endl;

}

void FitnessAppWrapper::editDailyDietPlan(vector<DietPlan>& weeklyDietPlans) {
	// first ask for the plan
	std::cout << "Input the diet plan: ";
	string plan;
	std::cin >> plan;
	// Now we need to search this plan in the vector, if this plan exists then we need to 
	// edit
	bool found = false;
	for (auto it = weeklyDietPlans.begin(); it != weeklyDietPlans.end(); ++it) {
		if (it->getName() == plan) {
			found = true;
			it->editGoal();
			std::cout << "Plan " << plan << " updated..." << std::endl;
		}
	}
	if (!found) {
		std::cout << "Plan: " << plan << " does not exists in the diet plans" << std::endl;
	}

}
void FitnessAppWrapper::editDailyExercisePlan(vector<ExercisePlan>& weeklyExercisePlans) {
	// first ask for the plan
	std::cout << "Input the diet plan: ";
	string plan;
	std::cin >> plan;
	// Now we need to search this plan in the vector, if this plan exists then we need to 
	// edit
	bool found = false;
	for (auto it = weeklyExercisePlans.begin(); it != weeklyExercisePlans.end(); ++it) {
		if (it->getName() == plan) {
			found = true;
			it->editGoal();
			std::cout << "Plan " << plan << " updated..." << std::endl;
		}
	}
	if (!found) {
		std::cout << "Plan: " << plan << " does not exists in the exercise plans" << std::endl;
	}
}