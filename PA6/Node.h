#ifndef _NODE
#define _NODE

#include<string>
using namespace std;

class Node
{
public:

	char eng;
	string morse;
	Node* right;
	Node* left;

public:
	Node();
	Node(string s);
	Node(char c);
	Node(char e, string s);
	string convert(char c);


};
#endif
