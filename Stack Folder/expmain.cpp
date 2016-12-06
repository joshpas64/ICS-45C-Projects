#include <iostream>
#include "Stacks.hpp"
#include "StackExchange.hpp"
#include <string>
#include <vector>

using namespace std;
typedef Stacks::Node Node;

int main()
{
	/*
	cout << "HELLO MI AMIGO!" << endl;
	StackExchange sE = StackExchange();
	sE.runStackExchange();
	*/
	vector<string> strVec;
	strVec.push_back("HELLO");
	strVec.erase(strVec.begin());
	cout << strVec.size() << endl;
	string start = "Hello there";
	char a = '!';
	start = start + a;
	cout << start << endl;

	return 0;
}