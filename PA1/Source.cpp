#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uintInvalid 999
#define floatInvalid 999


typedef enum sleep {
	NONE = 0,
	ASLEEP = 1,
	AWAKE = 2,
	REALLYAWAKE = 3,
	ABSENT_SLEEP_LEVEL = 4
} Sleep;



typedef struct fitbit {
	char patient[10];
	char minute[9];

	double calories;
	double distance;

	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;

} FitbitData;


char * my_strtok(char * str, char * deim, char ** context)
{
	char * location;
	char * ret = NULL;

	if (str != NULL) {
		*context = str;
	}

	if (*context != NULL)
	{
		location = strpbrk(*context, deim);
		if (location != NULL)
		{
			*location = 0;
			ret = *context;
			*context = ++location;
		}
		else {
			ret = *context;
		}
	}

	return ret;
}


int main(void) {

	FitbitData data[1445];
	FILE *dataFile = NULL;
	char targetID[10];
	int counter = 0;
	char * context = NULL;

	// Opening the file
	dataFile = fopen("FitbitData.csv", "r");
	if (dataFile == NULL) {
		//printf("FAILED TO OPEN THE FILE \n");
		return 0;
	}

	char buffer[1000] = "";
	char * token = NULL;
	//int i = 10;

	// Readin the first to extract the target ID x
	fgets(buffer, 1000, dataFile);
	token = strtok(buffer, ",");
	//printf("%s\n", token);

	token = strtok(NULL, ",");
	strcpy(targetID, token);
	//printf("%s\n", targetID);

	// Skipping the second line 
	fgets(buffer, 1000, dataFile);


	while (fgets(buffer, 1000, dataFile) != NULL)
	{


		////printf("%s\n", buffer);

		token = my_strtok(buffer, ",", &context);
		strncpy(data[counter].patient, token, 10);
		if (strcmp(targetID, token) == 0)
		{
			//	//printf("Target ID match\n");
			// minute,calories,distance,floors,heart,steps,sleep_level

			token = my_strtok(NULL, ",", &context);
			if (token != NULL)
			{
				strcpy(data[counter].minute, token);
			}

			token = my_strtok(NULL, ",", &context);
			if (token != NULL && strcmp("\0", token) != 0)
			{

				data[counter].calories = atof(token);
			}
			else
			{
				//printf("CALORIES ABSENT \n");
				data[counter].calories = floatInvalid;

			}


			token = my_strtok(NULL, ",", &context);
			if (token != NULL && strcmp("\0", token))
			{

				data[counter].distance = atof(token);
			}
			else
			{
				//printf("DISTANCE ABSENT \n");
				data[counter].distance = floatInvalid;
			}

			token = my_strtok(NULL, ",", &context);
			if (token != NULL)
			{
				data[counter].floors = atoi(token);
			}
			else
			{
				//printf("FLOORS ABSENT \n");
				data[counter].floors = uintInvalid;
			}


			token = my_strtok(NULL, ",", &context);
			if (token != NULL && strcmp("\0", token))
			{
				data[counter].heartRate = atoi(token);
			}
			else
			{
				//printf("HEARTRATE ABSENT \n");
				data[counter].heartRate = uintInvalid;
			}


			token = my_strtok(NULL, ",", &context);
			if (token != NULL && strcmp("\0", token))
			{
				data[counter].steps = atoi(token);
			}
			else
			{
				//printf("STEPS ABSENT \n");
				data[counter].steps = uintInvalid;
			}


			token = my_strtok(NULL, ",", &context);
			if (token != NULL && strcmp("\0", token))
			{
				data[counter].sleepLevel = (Sleep)atoi(token);
			}
			else
			{
				data[counter].sleepLevel = ABSENT_SLEEP_LEVEL;
				//printf("sleep level abset \n");
			}

			// incrementing the counter 
			counter++;
		}
		else
		{
			//printf("No match for target ID\n");
		}
	}
	unsigned int max_steps = 0;
	double total_distance = 0;
	double total_heartrate = 0;
	double sum_heartrate = 0;
	unsigned int total_floors = 0;
	unsigned int total_steps = 0;
	double total_calories = 0.0;


	int current_sleep_sum = 0,
		current_sleep_range = 0,
		current_sleep_pos = 0,
		max_sleep_sum = 0,
		max_sleep_range = 0;
	char current_sleep_start[9] = "",
		max_sleep_start[9] = "",
		max_sleep_end[9] = "";



	for (int i = 0; i <= 1440 - 1; i++)
	{
		if (data[i].calories != uintInvalid) {
			total_calories += data[i].calories;
		}

		if (data[i].steps != uintInvalid) {
			total_steps += data[i].steps;
		}

		if (data[i].floors != uintInvalid) {
			total_floors += data[i].floors;
		}

		if (data[i].heartRate != uintInvalid) {
			sum_heartrate += data[i].heartRate;
			total_heartrate++;
		}

		if (data[i].distance != uintInvalid) {
			total_distance += data[i].distance;
		}

		if (data[i].steps >= max_steps) {
			max_steps = data[i].steps;
		}

		if (i == 0) {
			strcpy(current_sleep_start, data[i].minute);
		}

		if (data[i].sleepLevel >= 1 && data[i].sleepLevel != ABSENT_SLEEP_LEVEL) {
			if (current_sleep_pos != i - 1) {
				current_sleep_sum = 0;
				current_sleep_range = 0;
				strcpy(current_sleep_start, data[i].minute);
			}

			//if the current sleep sum is larger than the total sleep sum, replace total sleep sum
			//if current sleep pos is reset, store the current minute
			//if i find a new max sleep sum overwrite min & max sleep sum with current values, and max sleep range

			if (current_sleep_sum > max_sleep_sum)
			{
				strcpy(max_sleep_start, current_sleep_start);
				strcpy(max_sleep_end, data[i].minute);
				max_sleep_sum = current_sleep_sum;
				max_sleep_range = current_sleep_range;
			}

			current_sleep_pos = i;
			current_sleep_sum += data[i].sleepLevel;
			current_sleep_range++;
		}
	}

	double avg_heartrate = sum_heartrate / total_heartrate;

	FILE *dataResults = NULL;
	dataResults = fopen("Results.csv", "w");
	if (dataResults == NULL) {
		printf("FAILED TO OPEN THE FILE \n");
	}

	fputs("Total Calories,Total Distance,Total Floors,Total Steps,Avg Heartrate,Max Steps,Sleep\n", dataResults);

	char secondLine[1000] = "";

	double total_miles = (double)total_steps / 2000.0;

	fprintf(dataResults, "%f,", total_calories);
	fprintf(dataResults, "%f,", total_miles);
	fprintf(dataResults, "%i,",  total_floors);
	fprintf(dataResults, "%i,",  total_steps);
	fprintf(dataResults, "%f,",  avg_heartrate);
	fprintf(dataResults, "%i,",  max_steps);
	fprintf(dataResults, "%s:",  max_sleep_start);
	fprintf(dataResults, "%s\n", max_sleep_end);



	for (int i = 0; i <= 1440 - 1; i++) {
		fprintf(dataResults, "%s,", data[i].patient);
		fprintf(dataResults, "%s,", data[i].minute);
		fprintf(dataResults, "%f,", data[i].calories);
		fprintf(dataResults, "%f,", data[i].distance);
		fprintf(dataResults, "%i,", data[i].floors);
		fprintf(dataResults, "%i,", data[i].heartRate);
		fprintf(dataResults, "%i,", data[i].steps);
		fprintf(dataResults, "%i\n", data[i].sleepLevel);
	}
	getchar();





	return 0;
}








