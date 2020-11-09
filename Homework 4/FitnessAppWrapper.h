#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

#include "DietPlan.h"
#include "ExercisePlan.h"

class FitnessAppWrapper {
private:
	vector <DietPlan> weeklyDietPlans;
	vector <ExercisePlan> weeklyExercisePlans;

	// fstreams for diet.txt
	fstream file_diet;
	// fstreams for exercise.txt
	fstream file_exercise;
	// ofstream outfile_exercise;

public:
	FitnessAppWrapper();
	void runApp(void);
	void displayMenu();

	void loadDailyDietPlan(fstream &fileStream, DietPlan &plan);
	void loadWeeklyDietPlan(fstream &fileStream, vector <DietPlan>& pWeeklyDietPlans);
	void displayDailyDietPlan(const DietPlan& dietPlan) const;
	void displayWeeklyDietPlan(const vector<DietPlan>& pWeeklyDietPlan) const;
	void storeDailyDietPlan(fstream& fileStream, DietPlan& dietPlan);
	void storeWeeklyDietPlan(fstream& fileStream, vector<DietPlan>& pWeeklyDietPlan);
	void editDailyDietPlan(vector<DietPlan>& weeklyDietPlans);

	void loadDailyExercisePlan(fstream &fileStream, ExercisePlan &plan);
	void loadWeeklyExercisePlan(fstream &fileStream, vector <ExercisePlan>& pWeeklyExercisePlans);
	void displayDailyExercisePlan(const ExercisePlan& exercisePlan) const;
	void displayWeeklyExercisePlan(const vector<ExercisePlan>& pWeeklyExercisePlan) const;
	void storeDailyExercisePlan(fstream& fileStream, ExercisePlan& exercisePlan);
	void storeWeeklyExercisePlan(fstream& fileStream, vector<ExercisePlan>& pWeeklyExercisePlan);
	void editDailyExercisePlan(vector<ExercisePlan>& weeklyExercisePlans);

};