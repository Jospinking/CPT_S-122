#include "List.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <stdio.h> 
#include <string.h> 
#include <sstream>

void show_menue();
void import_list(bool, string);
void load_master_list();
void store_master_list(string);
void mark_absences();
void generate_report();
void edit_absences();

List<Data>* master_list;


string timeToString(std::tm* now){
    string curr_date = to_string((now->tm_year + 1900)) + string(1,'-') + to_string((now->tm_mon + 1)) + string(1,'-') + to_string(now->tm_mday);
    return curr_date;
}

int main(){

	while(1){
		int choice;
		show_menue();

		cin >> choice;
		switch(choice){
			case 1: import_list(true, "classList.csv");
					break;
			case 2: load_master_list();
					break;
			case 3: store_master_list("master.txt");
					break;
			case 4: mark_absences();
					break;
			case 5: edit_absences();
					break;
			case 6: generate_report();
					break;
			case 7: cout << "Thanks for using attendance management software\n";
					return 0;
			default: std::cout << "Invalid choice\n";
					break;
		}
	}
}

void edit_absences(){
	Node<Data>* curr = master_list->head;
	while(curr != nullptr){
		std::cout << "Do you want to edit absences for following student:? (Y or N)";
		std::cout << curr->data.id << " " << curr->data.first_name << " " << curr->data.last_name << std::endl; 
		char choice;
		cin>> choice;
		if(choice == 'Y' or choice == 'y'){
			std::cout << "Number of absences for student: " << curr->data.absences << std::endl;
			std::cout << "Dates of absences: \n";
			Stack s = curr->data.absence_dates;
			int count = 1;
			while(!s.empty()){
				std::cout << count << ". " << timeToString(s.pop()) << std::endl;
				count++;
			}
			std::cout << "\n\n";
			if(curr->data.absences > 0){
				int edit;
				std::cout << "Which date do you want to make absent to present ? (Enter serial number as given above)\n ";
				cin >> edit;
				s = curr->data.absence_dates;
				Stack res;
				int count = 1;
				while(!s.empty()){
					if(count != edit){
						std::tm* t = s.pop();
						res.push(t);
					}
					else{
						s.pop();
					}
					count++;
				}
				while(!res.empty()){
					std::tm* t = res.pop();
					s.push(t);
				}
				curr->data.absence_dates = s;
				curr->data.absences--;
			}
		}
		curr = curr->next;
	}

}

void generate_report(){
	std::cout << "1. Get All student number of absent and recent absent date\n"; 
	std::cout << "2. Get Names of student absent for more than certain times\n";
	int choice;
	cin >> choice;
	if(choice == 1){
		Node<Data>* curr = master_list->head;
		while(curr != nullptr){
			if(!curr->data.absence_dates.empty()){
				std::cout << "Name of Student: " << curr->data.first_name << " " << curr->data.last_name << " Number of Times Absent: " << curr->data.absences << " Date of most recent absent " << timeToString(curr->data.absence_dates.peek()) << std::endl;
			}
			else{
				std::cout << "Name of Student: " << curr->data.first_name << " " << curr->data.last_name << " Number of Times Absent: " << curr->data.absences << std::endl;
			}
			curr = curr->next;
		}
		return;
	}
	if(choice == 2){
		int threshold;
		std::cout << "Enter the threshold for number of absent\n";
		cin >> threshold;
		Node<Data>* curr = master_list->head;
		while(curr != nullptr){
			if(curr->data.absences > threshold){
				std::cout << "Name of Student: " << curr->data.first_name << " " << curr->data.last_name << " Number of Times Absent: " << curr->data.absences << std::endl;
			}
			curr = curr->next;
		}
		return;
	}

}
void mark_absences(){
	std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);
	Node<Data>* curr = master_list->head;
	while(curr!=nullptr){
		std::cout << "Was Student " << curr->data.first_name<<" " << curr->data.last_name << " Present or Absent on " << timeToString(now)<< " ? (Type P for present and A for Absent) \n";
		char isabsent;
		cin >> isabsent;
		if(isabsent == 'A'){
			curr->data.absences++;
			curr->data.absence_dates.push(now);
		}
		curr = curr->next;
	}

}
void store_master_list(string filename){
	string header = "record_number,ID,Name,Email,Units,Program,Level";
	ofstream myfile (filename);
	if(myfile.is_open()){
		myfile << header << std::endl;
		Node<Data>* curr = master_list->head;
		while(curr!=nullptr){
			myfile<< curr->data.record_number 
			<< "," << curr->data.id 
			<< "," << curr->data.first_name
			<<","<< curr->data.last_name 
			<< "," << curr->data.email 
			<< "," << curr->data.units
			<< "," << curr->data.program
			<<"," << curr->data.level << std::endl;
			curr = curr->next;
		}
		myfile.close();
	}
}

void load_master_list(){
	import_list(false, "master.txt");
}

void import_list(bool deleteOld, string filename){

	if(deleteOld){
		master_list = nullptr;
		master_list = new List<Data>();
	}
	std::ifstream file(filename);
 
	std::string line = "";
	getline(file, line);
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::stringstream ss(line);

		int record_number;
		ss >> record_number;

		if (ss.peek() == ',')
	            ss.ignore();

		long id;
		ss >> id;
		
		if (ss.peek() == ',')
	            ss.ignore();

		string substr;

		getline( ss, substr, ',' );
		string first_name = substr.substr(1);
		
		getline( ss, substr, ',' );
		string last_name = substr.substr(0,substr.size() - 1);

		getline( ss, substr, ',' );
		string email = substr;

		getline( ss, substr, ',' );
		string units = substr;

		getline( ss, substr, ',' );
		string program = substr;

		getline( ss, substr, ',' );
		string level = substr;

		Data d(record_number, id, first_name, last_name,email, units, program, level);
	
		master_list->insertToFront(d);	 
	}
	std::cout << "\nImported to Master List completed !! \n";
	// Close the File
	file.close();
}


void show_menue(){
	std::cout << "Please select from following...\n";
	std::cout << "1. Import Course List\n";
	std::cout << "2. Load Master List\n";
	std::cout << "3. Store Master List\n";
	std::cout << "4. Mark Absences\n";
	std::cout << "5. Edit Absences\n";
	std::cout << "6. Generate Report\n";
	std::cout << "7. Exit\n";
}