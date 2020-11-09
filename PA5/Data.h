#pragma once
#include <iostream>

class Data
{
public: // Member functions

		// overloaded constructor
	Data(int customerNumber, int serviceTime, int totalTime);

	// accessors and mutators for the members
	int getCustomerNumber();
	void setCustomerNumber(int customerNumber);
	void setServiceTime(int serviceTime);
	int getServiceTime();
	void setTotalTime(int totalTime);
	int getTotalTime();

	void printData();

private:
	int customerNumber;
	int serviceTime;   
	int totalTime;     
}; // memory needs to be allocated on the heap!

Data::Data(int customerNumber, int serviceTime, int totalTime) {
	this->customerNumber = customerNumber;
	this->serviceTime = serviceTime;
	this->totalTime = totalTime;
}

int Data::getCustomerNumber() {
	return customerNumber;
}
void Data::setCustomerNumber(int customerNumber) {
	this->customerNumber = customerNumber;
}
void Data::setServiceTime(int serviceTime) {
	this->serviceTime = serviceTime;
}
int Data::getServiceTime() {
	return serviceTime;
}
void Data::setTotalTime(int totalTime) {
	
	this->totalTime = totalTime;
}
int Data::getTotalTime() {
	
	return this->totalTime;
}


void Data::printData() {
	std::cout << "Customer Number: " << this->getCustomerNumber() << std::endl;
	std::cout << "Service Time: " << this->getServiceTime() << " minutes. " << std::endl;
	std::cout << "Total Time: " << this->getTotalTime() << " minutes. " << std::endl;
	std::cout << std::endl;
}