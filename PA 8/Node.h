#pragma once


#include <string>

class Node
{
protected:
	std::string mData;
	Node* mpleft;
	Node* mpright;
public:
	Node(std::string data){
		mData = data;
		mpright = nullptr;
		mpleft = nullptr;
	}
	virtual ~Node(){}
	Node*& getmpleft(){
		return mpleft;
	}
	Node*& getmpright(){
		return mpright;
	}
	std::string getmData(){
		return mData;
	}
	void setmpright(Node* right){
		mpright = right;
	}
	void setmpleft(Node* left){
		mpleft = left;
	}
	void setData(std::string data){
		mData = data;
	}

	virtual void printData () = 0;

};