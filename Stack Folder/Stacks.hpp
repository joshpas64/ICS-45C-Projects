#ifndef STACKS_HPP
#define STACKS_HPP

#include <iostream>
#include <string>

class Stacks
{
public:
	struct Node
	{
	std::string someData;
	int someDigit;
	bool isTop;
	Node* prev;
	};
public:
	Stacks();
	Stacks(Node* node);
	~Stacks();
	int getSize() const;
	bool isEmpty() const;
	Node* getTop() const;
	std::string getTopData();
	int getTopDigits() const;
	Node* pop();
	void push(Node *node);
	void push(const std::string &data, int number);
	void exchange(Stacks &pushStack, bool order);
	void clear();
	std::string toString() const;
private:
	int currentLength;
	bool hasTop;
	Node* top;
	void makeCopyNode(Node *nodeTo, Node *nodeFrom);
};
#endif