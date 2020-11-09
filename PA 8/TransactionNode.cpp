#include "Node.h"
#include<iostream>
class TransactionNode: public Node
{
private: 
	int mUnits;

public:
	TransactionNode(std::string data, int units): Node(data), mUnits(units){

	}
	~TransactionNode(){

	}
	void setUnits(int units){
		mUnits = units;
	}
	int getUnits(){
		return mUnits;
	}

	void printData(){
		std::cout << mData << " " << mUnits << std::endl;
	}
};