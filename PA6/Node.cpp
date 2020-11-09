#include "BST.h"
#include <iostream>
#include <cstring>
#include <sstream>
Node::Node()
{
	left = NULL;
	right = NULL;
}

Node::Node(char c, string s)
{
	eng = c;
	morse = s;
}

Node::Node(string s)
{
	morse = s;
}
Node::Node(char c)
{
	eng = c;
	morse = convert(c);
}

string Node::convert(char c)
{
	if (c == ' ')
		return " ";
	else if (c == ',')
		return "--..--";
	else if (c == '.')
		return ".-.-.-";
	else if (c == '?')
		return "..--..";
	else if (c == '0')
		return "-----";
	else if (c == '1')
		return ".----";
	else if (c == '2')
		return "..---";
	else if (c == '3')
		return "...--";
	else if (c == '4')
		return "....-";
	else if (c == '5')
		return ".....";
	else if (c == '6')
		return "-....";
	else if (c == '7')
		return "--...";
	else if (c == '8')
		return "---..";
	else if (c == '9')
		return "----.";
	else if (c == 'A' || c == 'a')
		return ".-";
	else if (c == 'B' || c == 'b')
		return "-...";
	else if (c == 'C' || c == 'c')
		return "-.-.";
	else if (c == 'D' || c == 'd')
		return "-..";
	else if (c == 'E' || c == 'e')
		return ".";
	else if (c == 'F' || c == 'f')
		return "..-.";
	else if (c == 'G' || c == 'g')
		return "--.";
	else if (c == 'H' || c == 'h')
		return "....";
	else if (c == 'I' || c == 'i')
		return "..";
	else if (c == 'J' || c == 'j')
		return ".---";
	else if (c == 'K' || c == 'k')
		return "-.-";
	else if (c == 'L' || c == 'l')
		return ".-..";
	else if (c == 'M' || c == 'm')
		return "--";
	else if (c == 'N' || c == 'n')
		return "-.";
	else if (c == 'O' || c == 'o')
		return "---";
	else if (c == 'P' || c == 'p')
		return ".--.";
	else if (c == 'Q' || c == 'q')
		return "--.-";
	else if (c == 'R' || c == 'r')
		return ".-.";
	else if (c == 'S' || c == 's')
		return "...";
	else if (c == 'T' || c == 't')
		return "-";
	else if (c == 'U' || c == 'u')
		return "..-";
	else if (c == 'V' || c == 'v')
		return "...-";
	else if (c == 'W' || c == 'w')
		return ".--";
	else if (c == 'X' || c == 'x')
		return "-..-";
	else if (c == 'Y' || c == 'y')
		return "-.--";
	else if (c == 'Z' || c == 'z')
		return "--..";
	return "";
}